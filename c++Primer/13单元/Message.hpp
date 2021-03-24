#include <set>
#include <string>

class Message;
class Folder
{
    public:
    Folder(){ fol.clear(); }
    
    void AddMsg(Message* p){ fol.insert(p); }
    void DelMsg(Message* p){ fol.erase(p); }

    ~Folder(){  }
    private:
    std::set<Message*> fol;
};


class Message
{
    public:
    Message(const std::string& m = std::string()){ msg = m; fol.clear();}
    Message(const Message& m);

    Message& operator=(const Message& m);

    private:
    void PushMsgToFol();
    void PopMsgToFol();
    private:
    std::string msg;
    std::set<Folder*> fol;
}; 

void Message::PopMsgToFol()
{
    auto it = fol.begin();
    while(it != fol.end())
    {
        (*it)->DelMsg(this);
        ++it;
    }
}

void Message::PushMsgToFol()
{
    auto it = fol.begin();
    while(it != fol.end())
    {
        (*it)->AddMsg(this);
        ++it;
    }
}

Message::Message(const Message& m)
{
    msg = m.msg;
    fol = m.fol;
    PushMsgToFol();
}

Message& Message::operator=(const Message& m)
{
    if(this != &m)
    {
        //先将旧的消息从对应的文件夹中拿掉
        //再将新的消息写入&将新消息所在文件
        
    }
    return *this;
}
