#ifndef MYO_UTILS_H
#define MYO_UTILS_H

class MyoUtils {
        
    public:

        MyoUtils();  
        void resetMyo();      
        void runMyo();
        int getMyoTransition();
      
    private:

        void processBattery(int bat);                
        void ledEmg(int* emg);                
        
        void startThreadMyo();
        void joinThreadMyo(int timeout);
        void stopThreadMyo();
        void closeCondition(int* emg);            
        
        void getEmg();
        void processEmg(int* emg);
        void processImu(int quat, int acc, int gyro);
        void processSync(int arm, int x_direction);
        
};

#endif