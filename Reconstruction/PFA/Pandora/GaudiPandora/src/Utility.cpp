#include "Utility.h"

std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();   
}
dd4hep::rec::LayeredCalorimeterData * getExtension(unsigned int includeFlag, unsigned int excludeFlag=0) {
  
  
  dd4hep::rec::LayeredCalorimeterData * theExtension = 0;
  
  dd4hep::Detector & mainDetector = dd4hep::Detector::getInstance();
  const std::vector< dd4hep::DetElement>& theDetectors = dd4hep::DetectorSelector(mainDetector).detectors(  includeFlag, excludeFlag );
  
  
//  std::cout << " getExtension :  includeFlag: " << dd4hep::DetType( includeFlag ) << " excludeFlag: " << dd4hep::DetType( excludeFlag )
//                          << "  found : " << theDetectors.size() << "  - first det: " << theDetectors.at(0).name() << std::endl ;
  
  if( theDetectors.size()  != 1 ){
    
    std::stringstream es ;
    es << " getExtension: selection is not unique (or empty)  includeFlag: " << dd4hep::DetType( includeFlag ) << " excludeFlag: " << dd4hep::DetType( excludeFlag )
       << " --- found detectors : " ;
    for( unsigned i=0, N= theDetectors.size(); i<N ; ++i ){
      es << theDetectors.at(i).name() << ", " ; 
    }
    throw std::runtime_error( es.str() ) ;
  }
  
  theExtension = theDetectors.at(0).extension<dd4hep::rec::LayeredCalorimeterData>();
  
  return theExtension;
}


int partition(float x, float y)
{
    float a1, b1, a2, b2 ;
    if (x>1850 && x < 2020){
        line_a_b(1850, 750  , 2020, 600 , a1, b1);
        line_a_b(1850, -1000, 2020, -850, a2, b2);
        if ( (a1*x + b1*y) < 1 && (a2*x+b2*y) < 1 ) return 1 ;
    }
    if (y < 1850 && x < 2020){
        line_a_b(750 , 1850,2020, 600, a1, b1);
        line_a_b(1000, 1850,2020, 850, a2, b2);
        if( (a1*x + b1*y) > 1 && (a2*x+b2*y) < 1 ) return 2;
    }
    if (y < 2020 && y > 1850){
        line_a_b( -750, 1850 , -600, 2020 , a1, b1);
        line_a_b( 1000, 1850 , 850 , 2020 , a2, b2);
        if( (a1*x + b1*y) < 1 && (a2*x+b2*y) < 1 ) return 3;
    }
    if (y < 2020 && x > -1850){
        line_a_b(  -1850, 750  , -600 , 2020 , a1, b1);
        line_a_b(  -1850, 1000 , -850 , 2020 , a2, b2);
        if( (a1*x + b1*y) > 1 && (a2*x+b2*y) < 1 ) return 4;
    }
    if (x > -2020 && x < -1850){
        line_a_b( -1850, -750 ,  -2020, -600 , a1, b1);
        line_a_b( -1850, 1000 ,  -2020,  850 , a2, b2);
        if( (a1*x + b1*y) < 1 && (a2*x+b2*y) < 1 ) return 5;
    }
    if (x > -2020 && y > -1850){
        line_a_b( -750 , -1850 , -2020, -600 , a1, b1);
        line_a_b( -1000, -1850 , -2020, -850 , a2, b2);
        if( (a1*x + b1*y) > 1 && (a2*x+b2*y) < 1) return 6;
    }
    if (y > -2020 && y < -1850){
        line_a_b(  750 , -1850 ,  600, -2020 , a1, b1);
        line_a_b( -1000, -1850 , -850, -2020 , a2, b2);
        if( (a1*x + b1*y) < 1 && (a2*x+b2*y) < 1) return 7;
    }
    if (y > -2020 && x < 1850){
        line_a_b(  1850, -750  ,  600, -2020 , a1, b1);
        line_a_b(  1850, -1000 ,  850, -2020 , a2, b2);
        if( (a1*x + b1*y) > 1 && (a2*x+b2*y) < 1) return 8;
    }
    return -1;
}

void line_a_b(float x1, float y1, float x2, float y2, float& a, float& b)
{
    a = (y2-y1)/(x1*y2-x2*y1);
    b = (x1-x2)/(x1*y2-x2*y1);
}

float getPhi(float x, float y)
{
    if     (x==0 && y>0) return 90;
    else if(x==0 && y<0) return 270;
    else if(x==0 && y==0) return 0;
    float phi = atan(y/x)*180/acos(-1);
    if                 (x<0) phi = phi + 180;
    else if     (x>0 && y<0) phi = phi + 360;
    return phi;
}

int getStave(float x, float y){

int part = partition(x, y);
int Stave = part>=3 ? (part-2) : (part+6);// correct S is from 1 to 8, S-1 is from 0-7 
return Stave-1;
}

int getLayer(float x, float y, float z, std::vector<float>& layers){
if(abs(z) < 2400){
    float phi = getPhi(x, y);
    int part = partition(x, y);
    float rotated = (part-1)*45;
    float r = sqrt(x*x + y*y);
    const float PI = acos(-1);
    float new_x = r*cos((phi-rotated)*PI/180);
    float new_y = r*sin((phi-rotated)*PI/180);
    if(new_x <=layers.at(0)) return 0;
    if(new_x >=layers.at(layers.size()-1)) return 29;
    for(unsigned i=0; i<(layers.size()-1); i++){
        if(new_x >layers.at(i) && new_x <=layers.at(i+1) ) return i+1;
    }
}
else{
    if(abs(z) <=layers.at(0)) return 0;
    if(abs(z) >=layers.at(layers.size()-1)) return 29;
    for(unsigned i=0; i<(layers.size()-1); i++){
        if(abs(z) >layers.at(i) && abs(z) <=layers.at(i+1) ) return i+1;
    }

}
return -1;
}

int getLayer_v1(float x, float y, float z, std::vector<float>& layers){
if(abs(z) < 2400){
    float phi = getPhi(x, y);
    int part = partition(x, y);
    float rotated = (part-1)*45;
    float r = sqrt(x*x + y*y);
    const float PI = acos(-1);
    float new_x = r*cos((phi-rotated)*PI/180);
    float new_y = r*sin((phi-rotated)*PI/180);
    if(new_x <=layers.at(0)) return 1;
    if(new_x >=layers.at(layers.size()-1)) return layers.size();
    for(unsigned i=0; i<(layers.size()-1); i++){
        if(new_x >layers.at(i) && new_x <=layers.at(i+1) ) return i+2;
    }
}
else{
    if(abs(z) <=layers.at(0)) return 1;
    if(abs(z) >=layers.at(layers.size()-1)) return layers.size();
    for(unsigned i=0; i<(layers.size()-1); i++){
        if(abs(z) >layers.at(i) && abs(z) <=layers.at(i+1) ) return i+2;
    }

}
return -1;
}
