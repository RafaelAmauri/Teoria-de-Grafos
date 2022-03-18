# Graph-Based-Image-Segmentation
This project is an attempt to implement the research paper: [Efficient Graph Based Image Segmentation](http://people.cs.uchicago.edu/~pff/papers/seg-ijcv.pdf).
Entire bottom-up implementation done by the author (post-processing and rgb-color difference ideas taken from [here](http://cs.brown.edu/people/pfelzens/segment/)). I have also written an [article](https://iammohitm.github.io./Graph-Based-Image-Segmentation/) summarizing and explaining the research paper
 
### Requirements
1. C++ standard 17a
2. OpenCV
3. VTK

### Building and Execution
Run the commands in your project directory
```
mkdir source/build
cd source/build
cmake ../
make
```

# How to run
```
cd source/build

.\ImageSegment inputImage outputDir colorSpace k(float) sigma(float) minSize(int)
```

Explaining the variables 

 * k - the ammount of threshold
 * sigma - the ammount of blur
 * minSize - minimum component size
 * colorspace - can be "RGB" or "grayscale"

### License
[GNU-GPL](https://choosealicense.com/licenses/gpl-3.0/)