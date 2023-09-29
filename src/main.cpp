#include <Arduino.h>
#include "CommunicationPacks.hpp"
#include "UARTeensy.hpp"
#include "print.hpp"

CAN::IFToMaster packID1;
CAN::MasterToIF packID2;
CAN::MasterToIF packID3;
CAN::MasterToIF packID4;
CAN::MasterToIF packID5;

CAN::pack* canPackList[5] = {&packID1,&packID2,&packID3,&packID4,&packID5};
int canPackLen[5] = {sizeof(packID1),sizeof(packID2),sizeof(packID3),sizeof(packID4),sizeof(packID5)};

#include "CANpack.hpp"

CANpack canpack;

int cnt = 0;
unsigned long long last_print_time = 0;


// ----------------------------
// CHANGE HERE TO SET ID 
int ID = 1;
// ID range is 1 ~ 5
// -----------------------------

void setup() {
    canpack.CANsetup();
}

void loop() {
    Node.events();
    
    switch (ID){
    case 1:
        packID1.receiveState = 1;
        canpack.CANsend((ID-1),&packID1);
        break;
    case 2:
        packID2.receiveState = 1;
        canpack.CANsend((ID-1),&packID2);
        break;
    case 3:
        packID3.receiveState = 1;
        canpack.CANsend((ID-1),&packID3);
        break;
    case 4:
        packID4.receiveState = 1;
        canpack.CANsend((ID-1),&packID4);
        break;
    case 5:
        packID5.receiveState = 1;
        canpack.CANsend((ID-1),&packID5);
        break;    
    default:
        break;
    }

    if(millis() > last_print_time + 100U) {
        if(cnt % 4 == 0) {
            UTHAPS::print("| ");
            cnt = 0;
        } else if(cnt % 4 == 1) {
            UTHAPS::print("/ ");
        } else if(cnt % 4 == 2) {
            UTHAPS::print("- ");
        } else if(cnt % 4 == 3) {
            UTHAPS::print("\\ ");
        }
        bool ID1 = packID1.receiveState;
        bool ID2 = packID2.receiveState;
        bool ID3 = packID3.receiveState;
        bool ID4 = packID4.receiveState;
        bool ID5 = packID5.receiveState;
        UTHAPS::println("1 : ",ID1,"2 : ",ID2,"3 : ",ID3,"4 : ",ID4,"5 : ",ID5);
        packID1.receiveState = false;
        packID2.receiveState = false;
        packID3.receiveState = false;
        packID4.receiveState = false;
        packID5.receiveState = false;
        cnt ++;
    }

}
