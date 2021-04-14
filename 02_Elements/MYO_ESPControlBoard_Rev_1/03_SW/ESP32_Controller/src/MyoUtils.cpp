#include "MyoUtils.h"    

// TODO 2
// Myo Arm Band C++ Library 2

MyoUtils::MyoUtils(int mode){

    /*
        self.mode = mode
        self.transition = TRANSITION_TO_IDLE
        self.emg = [0]
        
        self.myo_mac_addr = myo.get_myo()
        
        logging.info("MYOUTILS - MAC address: %s", self.myo_mac_addr)    
        
        self.myo_device = myo.Device()
        self.myo_device.services.sleep_mode(1) # never sleep
        self.myo_device.services.set_leds([255, 255, 100], [255, 255, 100])
        self.myo_device.services.vibrate(1) # short vibration
        
        fw = self.myo_device.services.firmware()
        logging.info("MYOUTILS - Firmware version: %d.%d.%d.%d", fw[0], fw[1], fw[2], fw[3])
        batt = self.myo_device.services.battery()
        logging.info("MYOUTILS - Battery level: %d", batt)
        
        self.myo_device.services.emg_filt_notifications()
        self.myo_device.services.imu_notifications()
        self.myo_device.services.classifier_notifications()
        self.myo_device.services.set_mode(myo.EmgMode.FILT, myo.ImuMode.DATA, myo.ClassifierMode.ON)
        self.myo_device.add_emg_event_handler(self.process_emg)
        self.myo_device.add_emg_event_handler(self.led_emg)
        # self.myo_device.add_emg_event_handler(self.transition_emg)
        self.myo_device.add_sync_event_handler(self.process_sync)
        
        self.open = True

        */
}
        
void MyoUtils::startThreadMyo(){

    /*
    self.threadMyo = threading.Thread(target=self.runMyo, name="Thread-Myo")
    self.threadMyo.start()  
    time.sleep(2)
    */
}
        
void MyoUtils::joinThreadMyo(int timeout){

    /*
    self.threadMyo.join(timeout)
    */
}
        
void MyoUtils::stopThreadMyo(){

    /*
    self.threadMyo._stop()
    */

}
        
void MyoUtils::runMyo(){

    /*
    while True:
        if self.myo_device.services.waitForNotifications(1):
            continue
            logging.debug("MYOUTILS::runMyo - Waiting...")
    */
    }
    
void MyoUtils::getEmg(){

    /*
        logging.info("MYOUTILS::getEmg - emg value - [%i][%i][%i][%i][%i][%i][%i][%i]", self.emg[0], self.emg[1], self.emg[2], self.emg[3], self.emg[4], self.emg[5], self.emg[6], self.emg[7])
            
        return self.transition
    */
}        

void MyoUtils::processEmg(int* emg){

    /*
        #logging.info(emg)
        self.emg = emg
    */
}

void MyoUtils::processImu(int quat, int acc, int gyro){

    /*
    logging.debug(quat)
    */
}

void MyoUtils::processSync(int arm, int x_direction){

    /*
    logging.debug(arm, x_direction)
    */
}

void MyoUtils::processBattery(int bat){
    /*
    logging.debug("Battery level: %d", batt)
    */
}

void MyoUtils::ledEmg(int* emg){

    /*        
        if(self.closeCondition(emg)):
            self.myo_device.services.set_leds([255, 0, 0], [255, 0, 0])
        else:
            self.myo_device.services.set_leds([0, 255, 0], [0, 255, 0])
        */    
}       
                            
void MyoUtils::getMyoTransition(){
        
    /*
        lastTransition = self.transition
        
        logging.info("Listening...") 
        
        emg = self.emg
        while (self.transition == lastTransition or 
               self.transition == TRANSITION_TO_NOTHING):
            
            if(self.closeCondition(self.emg)):
                self.transition = TRANSITION_TO_CLOSE            
            else:
                self.transition = TRANSITION_TO_IDLE
         
            ## By the moment this conditions are the same
            if(self.transition == lastTransition):     
                self.transition = TRANSITION_TO_NOTHING
                
            emg = self.emg
            
                   
        logging.info("MYOUTILS::transition_emg - [%i][%i][%i][%i][%i][%i][%i][%i]", 
                     emg[0], emg[1], emg[2], emg[3], emg[4], emg[5], emg[6], emg[7])        
        logging.info("MYOUTILS::transition_emg - %i", self.transition)
            
        return self.transition

    */
}
    
                    
void MyoUtils::closeCondition(int* emg){

/*
    closeCondition = False
        
        #meanEmg = (emg[0] + emg[1] + emg[2] + emg[3] +  emg[4] + emg[5] + emg[6] + emg[7])/8
        #if (meanEmg > 300):
        
        #emg0Init = emg[0]
        #time.sleep(500)
        #emg0End = emg[0]
        #if(emgInit == 100 and emgFinal > 100):
        
        if(emg[0] > 100):
            closeCondition = True
        
        return closeCondition
        */  
}