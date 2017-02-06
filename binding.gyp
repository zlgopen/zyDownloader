{
  "targets": [
    {
      "target_name": "downloader",
      "sources": ["native/ymodem/fymodem.c", 
        "native/common/url.c",
        "native/common/common.c",
        "native/common/progress.c",
        "native/common/platform.c",
        "native/v8ext/addon.cc",
      	"native/streams/stream_tcp.c", 
      	"native/streams/stream_serial.cpp", 
        "native/transferers/transferer_tcp.c",
        "native/tftp/server_lib.c",
        "native/tftp/work_thread.c",
      	"native/serial/src/serial.cc", 
        "native/transferers/transferer_serial.cpp",
        "native/transferers/transferer_tftp_server.c",
        "native/transferers/transferer_factory.c"
	],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
       "native",
       "native/common",
       "native/ymodem",
       "native/streams",
       "native/transferers",
       "native/serial/include"
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        [
        'OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          },
          "sources": ["native/serial/src/impl/list_ports/list_ports_osx.cc","native/serial/src/impl/unix.cc"] 
        },
        'OS=="linux"', {
          "sources": ["native/serial/src/impl/list_ports/list_ports_linux.cc", "native/serial/src/impl/unix.cc"] 
        },
		'OS=="win"', { 
          "sources": ["native/serial/src/impl/list_ports/list_ports_win.cc","native/serial/src/impl/win.cc"],
		  'libraries': [
          '-lsetupapi.lib',
          '-lws2_32.lib'
        ]
        }]
      ]
    }
  ]
}
