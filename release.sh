rm -rf release electron
mkdir -p release/node_modules
mkdir -p release/Release/

cp -fv package.json release/package.json
cp -fv build/Release/*.node release/Release
cp -frv node_modules/bindings release/node_modules/bindings

for f in index.html	www
do
	cp -rfv $f release
done


