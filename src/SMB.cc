// $Id: SMB.cc 6219 2008-10-01 05:39:07Z vern $

#include "SMB.h"
#include "TCP_Reassembler.h"

SMB_Analyzer_binpac::SMB_Analyzer_binpac(Connection *c)
: TCP_ApplicationAnalyzer(AnalyzerTag::SMB, c)
	{
	interp = new binpac::SMB::SMB_Conn(this);
	}

SMB_Analyzer_binpac::~SMB_Analyzer_binpac()
	{
	delete interp;
	}

void SMB_Analyzer_binpac::Done()
	{
	TCP_ApplicationAnalyzer::Done();

	interp->FlowEOF(true);
	interp->FlowEOF(false);
	}

void SMB_Analyzer_binpac::EndpointEOF(TCP_Reassembler* endp)
	{
	TCP_ApplicationAnalyzer::EndpointEOF(endp);
	interp->FlowEOF(endp->IsOrig());
	}

void SMB_Analyzer_binpac::DeliverStream(int len, const u_char* data, bool orig)
	{
	TCP_ApplicationAnalyzer::DeliverStream(len, data, orig);

	assert(TCP());

	if ( TCP()->IsPartial() )
		// punt on partial.
		return;

	interp->NewData(orig, data, data + len);
	}

void SMB_Analyzer_binpac::Undelivered(int seq, int len, bool orig)
	{
	TCP_ApplicationAnalyzer::Undelivered(seq, len, orig);
	interp->NewGap(orig, len);
	}
