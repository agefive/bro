// See the file "COPYING" in the main distribution directory for copyright.

#ifndef smb_h
#define smb_h

#include "TCP.h"

#include "smb_pac.h"

class SMB_Analyzer_binpac : public TCP_ApplicationAnalyzer {
public:
	SMB_Analyzer_binpac(Connection* conn);
	virtual ~SMB_Analyzer_binpac();

	virtual void Done();
	virtual void DeliverStream(int len, const u_char* data, bool orig);
	virtual void Undelivered(int seq, int len, bool orig);
	virtual void EndpointEOF(TCP_Reassembler* endp);

	static Analyzer* InstantiateAnalyzer(Connection* conn)
		{ return new SMB_Analyzer_binpac(conn); }

	static bool Available()
        { return true; }

protected:
	binpac::SMB::SMB_Conn* interp;
};

#endif
