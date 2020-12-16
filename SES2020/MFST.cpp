#include "pch.h"

namespace MFST
{
	MfstState::MfstState()
	{
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
	};

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	};

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrule = pnrule;
		nrulechain = pnrulechain;
	};

	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	};

	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	};

	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; };

	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgreibach, Parm::PARM parm)
	{
		this->parm = parm;
		greibach = pgreibach;
		lex = plex;
		lenta_size = lex.size;
		lenta = new short[lenta_size];
		for (int k = 0; k < lenta_size; k++)
			lenta[k] = TS(lex.table[k].lexema);
		lenta_position = 0;
		st.push_back(greibach.stbottomT);
		st.push_back(greibach.startN);
		nrulechain = -1;
	};
	Mfst::RC_STEP Mfst::step()
	{
		RC_STEP rc = SURPRISE;
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.back()))
			{
				GRB::Rule rule;
				if ((nrule = greibach.getRule(st.back(), rule)) >= 0)
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						if (parm.debug)
							MFST_TRACE1
							saveState();
						st.pop_back();
						push_chain(chain);
						rc = NS_OK;
						if (parm.debug)
							MFST_TRACE2
					}
					else
					{
						if (parm.debug)
							MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE")
							saveDiagnosis(NS_NORULECHAIN); rc = restState() ? NS_NORULECHAIN : NS_NORULE;
					};
				}
				else
					rc = NS_ERROR;
			}
			else if ((st.back() == lenta[lenta_position]))
			{
				lenta_position++; st.pop_back(); nrulechain = -1; rc = TS_OK;
				if (parm.debug)
					MFST_TRACE3
			}
			else
			{
				if (parm.debug)
					MFST_TRACE4("TS_NOK/NS_NORULECHAIN")
					rc = restState() ? TS_NOK : NS_NORULECHAIN;
			};
		}
		else
		{
			rc = LENTA_END;
			if (parm.debug)
				MFST_TRACE4("LENTA_END")
		};
		return rc;
	};

	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		for (int k = chain.size - 1; k >= 0; k--)
			st.push_back(chain.nt[k]);
		return true;
	};

	bool Mfst::saveState()
	{
		storestate.push_back(MfstState(lenta_position, st, nrule, nrulechain));
		if (parm.debug)
			MFST_TRACE6("SAVESTATE:", storestate.size());
		return true;
	};

	bool Mfst::restState()
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.back();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop_back();
			if (parm.debug)
			{
				MFST_TRACE5("RESSTATE")
					MFST_TRACE2
			}

		};
		return rc;
	};

	bool Mfst::saveDiagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position)
			k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++)
				diagnosis[j].lenta_position = -1;
		};
		return rc;
	};

	bool Mfst::start()
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step();
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step();

		switch (rc_step)
		{
		case LENTA_END:
			if (parm.debug)
			{
				MFST_TRACE4("------>LENTA_END")
					std::cout << "-------------------------------------------------------------------------" << std::endl;
				sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
				std::cout << std::setw(4) << std::left << 0 << ": всего строк " << lenta_size << ", синтаксический анализ выполнен без ошибок" << std::endl;
			}
			rc = true;
			break;
		case NS_NORULE:
			if (parm.debug)
			{
				MFST_TRACE4("------>NS_NORULE")
					std::cout << "-------------------------------------------------------------------------" << std::endl;
				/*std::cout << getDiagnosis(0, buf) << std::endl;
				std::cout << getDiagnosis(1, buf) << std::endl;*/
				std::cout << getDiagnosis(0, buf) << std::endl;
			}
			break;
		case NS_NORULECHAIN:
			if (parm.debug)
				MFST_TRACE4("------>NS_NORULECHAIN")
				break;
		case NS_ERROR:
			if (parm.debug)
				MFST_TRACE4("------>NS_ERROR")
				break;
		case SURPRISE:
			if (parm.debug)
				MFST_TRACE4("------>SURPRISE")
				break;
		};
		return rc;
	};

	char* Mfst::getCSt(char* buf)
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = st[k];
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		};
		buf[st.size()] = 0x00;
		return buf;
	};

	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	};

	char* Mfst::getDiagnosis(short n, char* buf)
	{
		char* rc = (char*)"";
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = greibach.getRule(diagnosis[n].nrule).iderror;
			throw ERROR_THROW_IN(errid, lex.table[lpos].sn, -1);
			/*Error::ERROR err = Error::geterror(errid);
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: строка %d, %s", err.id, lex.table[lpos].sn, err.message);
			rc = buf;*/
		};
		return rc;
	};

	void Mfst::printRules()
	{
		MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate[k];
			rule = greibach.getRule(state.nrule);
			MFST_TRACE7
		};
	};

	bool Mfst::saveDeducation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.size = storestate.size();
		deducation.nrules = new short[deducation.size];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); k++)
		{
			state = storestate[k];
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		};
		return true;
	}
};