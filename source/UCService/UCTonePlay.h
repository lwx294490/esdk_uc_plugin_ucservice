#ifndef _UC_TONE_PLAY_
#define _UC_TONE_PLAY_

class UCTonePlay
{
public:
	static inline UCTonePlay& Instance()
	{
		return *ctk::Singleton_T<UCTonePlay>::instance(CTK_CURRENT);
	}
	int StartPlayIncomingCall(void) const;	
	int EndPlay(void) const;
	int StartPlayRingBack(void) const;//≤•∑≈ªÿ¡Â“Ù
	int PlayDTMFTone(char tone) const;
public:
	UCTonePlay(void);
	~UCTonePlay(void);
private:
	std::string m_curPath;
};
#endif


