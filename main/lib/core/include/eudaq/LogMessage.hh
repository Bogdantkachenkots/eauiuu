#ifndef EUDAQ_INCLUDED_LogMessage
#define EUDAQ_INCLUDED_LogMessage

#include <string>
#include <vector>

#include "eudaq/Serializable.hh"
#include "eudaq/Serializer.hh"
#include "eudaq/Deserializer.hh"
#include "eudaq/Status.hh"
#include "eudaq/Time.hh"
#include "eudaq/Platform.hh"

namespace eudaq {

  class DLLEXPORT LogMessage : public Status {
  public:
    LogMessage(const std::string &msg = "", Level level = LVL_EXTRA,
               const Time &t = Time::Current());
    LogMessage(Deserializer &);
    virtual void Serialize(Serializer &) const override;
    virtual void Print(std::ostream &, size_t offset = 0) const override;
    void Write(std::ostream &) const;
    static LogMessage Read(std::istream &);
    LogMessage &SetLocation(const std::string &file, unsigned line,
                            const std::string &func = "");
    LogMessage &SetSender(const std::string &name);
    std::string GetSender() const {
      return m_sendertype +
             (m_sendername == "" ? std::string("") : "." + m_sendername);
    }
    std::string GetSenderType() const { return m_sendertype; }
    std::string GetSenderName() const { return m_sendername; }

  protected:
    std::string m_file, m_func, m_sendertype, m_sendername;
    unsigned m_line;
    Time m_time, m_createtime;
  };

  inline std::ostream &operator<<(std::ostream &os, const LogMessage &ev) {
    ev.Print(os);
    return os;
  }
}

#endif // EUDAQ_INCLUDED_LogMessage
