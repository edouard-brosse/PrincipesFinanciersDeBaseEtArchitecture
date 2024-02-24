#include <iostream>
#include <vector>
#include <string>

class FixLib {
    private: 
        // "35=D" : "NewOrder"
        // "35=G" : OrderCancel / Replace Request
        // "35=9" : Order Cancel Request

        /* header :         // NE change pas  // https://www.onixs.biz/fix-dictionary/4.2/compblock_standardheader.html
            8	BeginString //  8 |Version de FIX
            9	BodyLength //  9 |Longueur du corps
            35	MsgType  == //  35 |Type de message
            49	SenderCompID //  49 |ID de l'envoyeur
            56	TargetCompID //  56 |ID du receveur
            34	MsgSeqNum     //  34 |Numero de la requette  compeur de message par utilisateur continuer la suite de chifre (voir mechanisme champ 141)
            52	SendingTime //  52 |Heure d'envoie
        */
        
        /* body :   // CHANGE
            new  order fields: (update order to) https://www.onixs.biz/fix-dictionary/4.2/msgtype_d_68.html
                11	ClOrdID	Y	Unique identifier of the order as assigned by institution.
                21	HandlInst	Y
                55	Symbol	Y
                54	Side	Y
                60	TransactTime	Y	Time this order request was initiated/released by the trader or trading system.
                40	OrdType	Y
            
            Order Cancel Request: https://www.onixs.biz/fix-dictionary/4.2/msgtype_f_70.html
                41	OrigClOrdID	Y
                11	ClOrdID	Y
                55	Symbol	Y
                54	Side	Y
                60	TransactTime	Y
            
            commande pour voir les ordre en dehors du protocol Fix ?

        */
        // trailer  // NE change pas https://www.onixs.biz/fix-dictionary/4.3/compBlock_StandardTrailer.html
        //  10 Checkum 
        std::unordered_map<std::string, std::string> HeaderLib;
        std::unordered_map<std::string, std::string> BodyLib;
        std::unordered_map<std::string, std::string> TrailLib;
        struct BodyLib {
            std::string ID;
            std::string Content;
            BodyLib(std::string id, std::string content) : ID(id), Content(content) {}
        };
    public:
        initLib(){
            HeaderLib["8"] = "BeginString";
            HeaderLib["9"] = "BodyLength";
            HeaderLib["35"] = "MsgType";
            HeaderLib["49"] = "SenderCompID";
            HeaderLib["56"] = "TargetCompID";
            HeaderLib["34"] = "MsgSeqNum";
            HeaderLib["52"] = "SendingTime";
            BodyLib["11"] = "ClOrdID";
            BodyLib["21"] = "HandlInst";
            BodyLib["55"] = "Symbol";
            BodyLib["54"] = "Side";
            BodyLib["60"] = "TransactTime";
            BodyLib["40"] = "OrdType";
            TrailLib["10"] = "Checkum";

            //// ou 

            BodyLib.push_back(BodyLib("11", "ClOrdID"));
            BodyLib.push_back(BodyLib("21", "HandlInst"));
        }

        // faut t'il faire plusieurs lib ou une seul suffit ?


     //https://www.onixs.biz/fix-dictionary/4.2/app_d.html
    // 8=FIX.4.2^9=76^35=A^49=BuySide^56=SellSide^34=1^52=20190605-11:27:06.897^98=0^108=30^141=Y^10=008^
};

// Add Order 10 340

class addOrder : FixLib {
    private:

    public:

};

// login  https://www.onixs.biz/fix-dictionary/4.3/msgtype_a_65.html#
// logout  

// add order        >> CreateOrder DecodeOrder
// add sellOrder    >> CreateSellOrder DecodeSellOrder
// update order     >> UpdateOrder DecodeUpdateOrder
// remove order

// see my order
// see all order

// prix 100 quantité 3

