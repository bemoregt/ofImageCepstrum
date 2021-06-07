#include "ofApp.h"
using namespace ofxCv;

using namespace cv;
using namespace std;

// functions ------------------------------------------
void dft_shift(Mat& ds)
{
    int cx = ds.cols / 2;
    int cy = ds.rows / 2;
    Mat q0 = ds(cv::Rect(0, 0, cx, cy));
    Mat q1 = ds(cv::Rect(cx, 0, cx, cy));
    Mat q2 = ds(cv::Rect(0, cy, cx, cy));
    Mat q3 = ds(cv::Rect(cx, cy, cx, cy));
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

// calc magnitude -------------------------------------
// cv method overide ----------------------------------
void magnitude(Mat &input_img, Mat &magnitude_img)
{
    Mat planes[2];
    split(input_img, planes);
    cv::magnitude(planes[0], planes[1], magnitude_img);
}

void magnitude2(Mat input_img, Mat magnitude_img)
{
    //Mat planes[2];
    //split(input_img, planes);
    cv::magnitude(input_img, input_img, magnitude_img);
}

//
ofImage show_spectrum(Mat& img_spectrum, bool inverse)
{
    Mat img;
    magnitude(img_spectrum, img);

    img += Scalar::all(1);
    log(img, img);
    
    normalize(img, img, 0, 255, NORM_MINMAX);
    img.convertTo(img, CV_8UC1);
    
    ofImage of1;
    toOf(img, of1);
    //of1.update();
    return of1;
    
}

// -----------------------------------------------------------
ofImage show_cepstrum(Mat& img_spectrum, bool inverse)
{
    // 1. 절대값 구하기
    Mat img;
    magnitude(img_spectrum, img);
    // 2. 로그 취하기
    log(img, img);
    
    // 3. 역 푸리에 변환
    Mat dtft_mat;
    dft(img, dtft_mat, DFT_INVERSE);
    dft_shift(dtft_mat);
    // 4. 디스플레이 를 위한 강조
    magnitude2(dtft_mat, img);
    img += Scalar::all(1);
    log(img, img);
    // 5. 정규화
    normalize(img, img, 0, 255, NORM_MINMAX);
    img.convertTo(img, CV_8UC1);
    
    ofImage of1;
    toOf(img, of1);
    //of1.update();
    return of1;
    
}
//--------------------------------------------------------------
void ofApp::setup(){

    //Mat src_img = cv::imread("lena1.jpg", 0);
    filePath = "/Users/user1/Desktop/cam.png";
    before.load(filePath);
    cv::Mat src_img = toCv(before);
    
    if (!src_img.data) {
        return 0;
    }

    //imshow("src img", src_img);
    src_img.convertTo(src_img, CV_64FC1);
    Mat img_spectrum(src_img.size(), CV_64FC2);

    dft(src_img, img_spectrum, DFT_COMPLEX_OUTPUT, 0);
    dft_shift(img_spectrum);

    spect= show_spectrum(img_spectrum, false);
    spect.update();
    
    
    //========================
    
    cepst= show_cepstrum(img_spectrum, false);
    cepst.update();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255,255,255);
    before.draw(0, 0, 512, 512);
    spect.draw(512, 0, 512, 512);
    cepst.draw(1024, 0, 512, 512);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
