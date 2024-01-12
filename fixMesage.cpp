#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class FixMessage{
    public:
        struct Logon
        {
        };
        

        void FixLogOnMaker () {
            //std::cout << fixVer << splitChar  ;
    }

    private:
        char *splitChar = "^";
        std::unordered_map<std::string, int> TagDictionary;
        std::unordered_map<int, int> TagDictionar;
        //TagDictionary["8"] = 0;
        TagDictionar[8] = 0;
        void Header () {
        }

        void Footer(){
        }

    protected:

};

/*
    //Header
    8   : BeginString
    9   : BodyLength
    35  : MsgType
    49  : senderCompID
    56  : TargetCompID
    35  : MsgSeqNum
    52  : SendingTime

    // LogOn
    108 : HeartBtInt
    98  : EncryptMethod

    //footer
    10 : CheckSum
8=FIX.4.3^9=102^35=A^49=BuySide^56=SellSide^52=20190605-11:37:55.565^98=0^108=30^10=118^


*/

/* 
messages:
    - Logon         => https://www.onixs.biz/fix-dictionary/4.3/msgtype_a_65.html#
    - New Order     =>
    - Order Ack     =>
    - Logout        => https://www.onixs.biz/fix-dictionary/4.3/msgType_5_5.html
    ... message type
    8=FIX.4.3^9=102^35=A^49=BuySide^56=SellSide^34=1^52=20190605-11:37:55.565^98=0^108=30^141=Y^553=Username^554=Password^10=118^

*/

/*
    faire un heritage :
        chaque classe corespond a un msg et herite de la class (FixMessage)
        contient les champs header / footer
        dictionaire contenant les champ du body, header, footer
        geter, setter
        addField (protected)


    class fille example: Logon
        encapsulation 
        setter champ qui exist


    


    serialisation
    Deserialisation

    implementer une class fille Decoded message (instancier avec une taille de buffer)
        getField
*/

