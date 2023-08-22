# LabBMP

A simple realisation of game of life

To run the app, type in cmd:

    git clone https://github.com/TGontar/LabBMP
    cd LabBMP
    cd cmake-build-debug
    LabBMP.exe --flags

Usage of the flags:

    --input "/filepath/" - required flag, the path to the original monochrome bmp file with the 1st genetation
    --output "/filepath/" - required flag, the directory where output image will be created
    --max_iter - the maximium amount of generations to make
    --dump_freq - the frequency of saving image to output file