# ofImageCepstrum
Image Cepstrum using OF for Blind Deblurring.

![cepst example]( https://github.com/bemoregt/ofImageCepstrum/blob/master/shot1.png "example")

![cepst example2]( https://github.com/bemoregt/ofImageCepstrum/blob/master/sho21.png "example2")
- Motion Blurred Image, 2D Spectrum, Image Cepstrum.

### Algorithm
- Cepstrum is used to find PSF function of blurred image.
- Image > FFT2() > abs() > log() > iFFT2()

### Dependancy
- Openframeworks 0.11.x
- ofxCv, ofxOpenCV
- XCode 11.1
- OSX Catalina

### Next Plan
- Post Processing for Highlight Peaks.
