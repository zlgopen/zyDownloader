/* -*- encoding: utf-8; -*- */
/* -*- c-mode -*- */
/* File-name:    <url.c> */
/* Author:       <Xsoda> */
/* Create:       <Friday December 20 12:38:02 2013> */
/* Time-stamp:   <Wednesday December 25, 10:10:57 2013> */
/* Mail:         <Xsoda@Live.com> */

#include "url.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

static void url_free(url_t *url);
static char *str_hosttype[] = { "host ipv4", "host ipv6", "host domain", NULL };

static char *mystrndup(const char *str, size_t n)
{
   char *dst;
   if (!str) return NULL;
   if (n >= 0xffffffff) n = strlen(str);
   if (n == 0) return NULL;
   if ((dst = (char *)malloc(n + 1)) == NULL)
      return NULL;
   memcpy(dst, str, n);
   dst[n] = 0;
   return dst;
}

static int host_is_ipv4(char *str)
{
   if (!str) return 0;
   while (*str)
   {
      if ((*str >= '0' && *str <= '9') || *str == '.')
         str++;
      else
         return 0;
   }
   return 1;
}

void parse_query(url_t *url, char *query)
{
   size_t length;
   size_t offset;
   char *chr;
   length = strlen(query);
   offset = 0;
   chr = strchr(query, '=');
   while (chr)
   {
      if (url->query)
         url->query = realloc(url->query, (url->query_num + 1) * sizeof(*url->query));
      else
         url->query = malloc(sizeof(*url->query));
      url->query[url->query_num].name = mystrndup(query, chr - query);
      query = chr + 1;
      chr = strchr(query, '&');
      if (chr)
      {
         url->query[url->query_num].value = mystrndup(query, chr - query);
         url->query_num++;
         query = chr + 1;
         chr = strchr(query, '=');
      }
      else
      {
         url->query[url->query_num].value = mystrndup(query, -1);
         url->query_num++;
         break;
      }
   }
}

static url_t* url_create() 
{
      url_t *url = (url_t*)calloc(sizeof(url_t), 1);
      if(url) {
            url->ref = 1;
      }

      return url;
}

url_t *url_parse (const char *str)
{
   const char *pch;
   char *query;
   query = NULL;
   url_t *url = url_create();

   if (str && str[0])
   {
      url->href = mystrndup(str, -1);
      pch = strchr(str, ':');   /* parse schema */
      if (pch && pch[1] == '/' && pch[2] == '/')
      {
         url->schema = mystrndup(str, pch - str);
         str = pch + 3;
      }
      else
         goto __fail;
      pch = strchr(str, '@');   /* parse user info */
      if (pch)
      {
         pch = strchr(str, ':');
         if (pch)
         {
            url->username = mystrndup(str, pch - str);
            str = pch + 1;
            pch = strchr(str, '@');
            if (pch)
            {
               url->password = mystrndup(str, pch - str);
               str = pch + 1;
            }
            else
               goto __fail;
         }
         else
            goto __fail;
      }
      if (str[0] == '[')        /* parse host info */
      {
         str++;
         pch = strchr(str, ']');
         if (pch)
         {
            url->host = mystrndup(str, pch - str);
            str = pch + 1;
            if (str[0] == ':')
            {
               str++;
               pch = strchr(str, '/');
               if (pch)
               {
                  url->port = mystrndup(str, pch - str);
                  str = pch + 1;
               }
               else
               {
                  url->port = mystrndup(str, -1);
                  str = str + strlen(str);
               }
            }
            url->host_type = HOST_IPV6;
         }
         else
            goto __fail;
      }
      else
      {
         const char *pch_slash;
         pch = strchr(str, ':');
         pch_slash = strchr(str, '/');
         if (pch && (!pch_slash || (pch_slash && pch<pch_slash)))
         {
            url->host = mystrndup(str, pch - str);
            str = pch + 1;
            pch = strchr(str, '/');
            if (pch)
            {
               url->port = mystrndup(str, pch - str);
               str = pch + 1;
            }
            else
            {
               url->port = mystrndup(str, -1);
               str = str + strlen(str);
            }
         }
         else
         {
            pch = strchr(str, '/');
            if (pch)
            {
               url->host = mystrndup(str, pch - str);
               str = pch + 1;
            }
            else
            {
               url->host = mystrndup(str, -1);
               str = str + strlen(str);
            }
         }
         url->host_type = host_is_ipv4(url->host) ? HOST_IPV4 : HOST_DOMAIN;
      }
      if (str[0])               /* parse path, query and fragment */
      {
         pch = strchr(str, '?');
         if (pch)
         {
            url->path = mystrndup(str, pch - str);
            str = pch + 1;
            pch = strchr(str, '#');
            if (pch)
            {
               query = mystrndup(str, pch - str);
               str = pch + 1;
               url->fragment = mystrndup(str, -1);
            }
            else
            {
               query = mystrndup(str, -1);
               str = str + strlen(str);
            }
            parse_query(url, query);
            free(query);
         }
         else
         {
            pch = strchr(str, '#');
            if (pch)
            {
               url->path = mystrndup(str, pch - str);
               str = pch + 1;
               url->fragment = mystrndup(str, -1);
               str = str + strlen(str);
            }
            else
            {
               url->path = mystrndup(str, -1);
               str = str + strlen(str);
            }
         }
      }
   }
   else
   {
__fail:
      url_free(url);
      return NULL;
   }

   if(url->path) {
   	   url->filename = get_file_name(url->path); 
   	   char* path = url->path;
       char* filename = strrchr(path, '/');
       if(!filename) {
            filename = strrchr(path, '\\');
       }

       if(filename) {
       	   url->dir = mystrndup(path, filename-path);
       	   filename++;
       }else{
	       filename = path;
	       url->dir = mystrndup("/", 1);
       }
   }

   return url;
}

static void url_free(url_t *url)
{
   if (!url) return;
   if (url->href) free(url->href);
   if (url->schema) free(url->schema);
   if (url->username) free(url->username);
   if (url->password) free(url->password);
   if (url->host) free(url->host);
   if (url->port) free(url->port);
   if (url->path) free(url->path);
   if (url->dir) free(url->dir);
   if (url->query)
   {
      int i;
      for (i = 0; i < url->query_num; i++)
      {
         free(url->query[i].name);
         free(url->query[i].value);
      }
      free(url->query);
   }
   if (url->fragment) free(url->fragment);
   free(url);
}

url_t *url_ref(url_t *url) {
      if(url) {
            url->ref++;
      }

      return url;
}

void url_unref(url_t *url) {
      if(url && url->ref > 0) {
            url->ref--;
            if(url->ref < 1) {
                  url_free(url);
            }
      }
}


void url_print(url_t *url)
{
   if (!url) return;
   fprintf(stdout, "\nurl field:\n");
   fprintf(stdout, "  - href:     '%s'\n", url->href);
   fprintf(stdout, "  - schema:   '%s'\n", url->schema);
   if (url->username)
      fprintf(stdout, "  - username: '%s'\n", url->username);
   if (url->password)
      fprintf(stdout, "  - password: '%s'\n", url->password);
   fprintf(stdout, "  - host:     '%s' (%s)\n", url->host, str_hosttype[url->host_type]);
   if (url->port)
      fprintf(stdout, "  - port:     '%s'\n", url->port);
   if (url->path)
   fprintf(stdout, "  - path:     '%s'\n", url->path);
   if (url->dir)
   fprintf(stdout, "  - dir:     '%s'\n", url->dir);
   if (url->filename)
   fprintf(stdout, "  - filename:     '%s'\n", url->filename);
   if (url->query_num > 0)
   {
      int i;
      fprintf(stdout, "  - query\n");
      for (i = 0; i < url->query_num; i++)
      {
         fprintf(stdout, "    * %s : %s\n", url->query[i].name, url->query[i].value);
      }
   }
   if (url->fragment)
      fprintf(stdout, "  - fragment: '%s'\n", url->fragment);
}

const char* url_get_param(url_t *url, const char* name) {
	int n = url->query_num;
	for(int i = 0; i < n; i++) {
		if(strcmp(url->query[i].name, name) == 0) {
			return url->query[i].value;
		}
	}
	
	return NULL;
}

