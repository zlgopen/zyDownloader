ifeq ($(OS),Windows_NT)
  export RM=rmdir /S /Q
  export MV=move /Y
  export ELECTRON_VERSION=$(subst v,, $(shell node_modules\.bin\electron -v))
else
  export RM=rm -rf
  export MV=mv -vf
  export ELECTRON_VERSION=$(subst v,, $(shell node_modules/.bin/electron -v))
endif


all:
	prebuild -b $(ELECTRON_VERSION) -t $(ELECTRON_VERSION) -r electron
	npm run build

clean:
	$(RM) stderr.txt stdout.txt js build prebuilds release

config:
	node-gyp configure
