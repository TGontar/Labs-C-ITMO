#LabMP3

A simple mp3 tag editor

To run the app open cmd and type:

	git clone "https://github.com/TGontar/LabMP3"
	
	cd LabMP3
	
	cd cmake-build-debug
	
	LabMusic.exe --flags

Usage of flags:

	--filepath="" - path of your mp3 file
	
	--show - show all metainfo
	
	--set="tag" --value="val" - set the tag "tag" the value "val"
	
	--get="tag" - get the data of the tag "tag"
	