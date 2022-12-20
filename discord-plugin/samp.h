#pragma once
#include <string>
#include <cstdint>
#include <windows.h>


#if defined (SAMP_R1_COMPILE)
//pointers to structs
#define SAMP_INFO_OFFSET				0x21A0F8U
#define SAMP_CHAT_INFO_OFFSET 			0x21A0E4U
#define SAMP_CHAT_INPUT_INFO_OFFSET		0x21A0E8U
#define SAMP_KILL_INFO_OFFSET			0x21A0ECU
#define SAMP_DIALOG_INFO_OFFSET 		0x21A0B8U
#define SAMP_MISC_INFO_OFFSET			0x21A10CU
#define SAMP_SCOREBOARD_INFO_OFFSET		0x21A0B4U
//hooks addresses
#define SAMP_RAKCLIENT_SEND				0x00307F0U
#define SAMP_RAKCLIENT_RPC_SEND			0x0030B30U
#define SAMP_RAKPEER_HANDLE_RPC_PACKET	0x00372F0U
#define SAMP_RAKPEER_RECEIVE			0x0031180U
#elif defined (SAMP_R3_COMPILE)
//pointers to structs
#define SAMP_INFO_OFFSET				0x26E8DCU
#define SAMP_CHAT_INFO_OFFSET 			0x26E8C8U
#define SAMP_CHAT_INPUT_INFO_OFFSET		0x26E8CCU
#define SAMP_KILL_INFO_OFFSET			0x26E8D0U
#define SAMP_DIALOG_INFO_OFFSET 		0x26E898U
#define SAMP_MISC_INFO_OFFSET			0x26E8F4U
#define SAMP_SCOREBOARD_INFO_OFFSET		0x26E894U
//hooks address
#define SAMP_RAKCLIENT_SEND				0x0033BA0U
#define SAMP_RAKCLIENT_RPC_SEND			0x0033EE0U
#define SAMP_RAKPEER_HANDLE_RPC_PACKET	0x003A6A0U
#define SAMP_RAKPEER_RECEIVE			0x0034530U
#endif

class RakPeerInterface {};
class RakClientInterface {};

#if defined (SAMP_R1_COMPILE)
#pragma pack(push, 1)
struct stSAMPPools
{
	struct stActorPool*			pActor;
	struct stObjectPool*		pObject;
	struct stGangzonePool*		pGangzone;
	struct stTextLabelPool*		pText3D;
	struct stTextdrawPool*		pTextdraw;
	void*						pPlayerLabels;
	struct stPlayerPool*		pPlayer;
	struct stVehiclePool*		pVehicle;
	struct stPickupPool*		pPickup;
};
struct stSAMP
{
	void*						pUnk0;
	struct stServerInfo*		pServerInfo;
	uint8_t						byteSpace[24];
	char						szIP[257];
	char						szHostname[259];
	bool						bNametagStatus;
	uint32_t					ulPort;
	uint32_t					ulMapIcons[100];
	int							iLanMode;
	int							iGameState;
	uint32_t					ulConnectTick;
	struct						stServerPresets* pSettings;
	void*						pRakClientInterface;
	struct stSAMPPools*			pPools;
};
struct stPlayerPool
{
	uint32_t					ulMaxPlayerID;
	uint16_t					sLocalPlayerID;
	void*						pVTBL_txtHandler;
	std::string					strLocalPlayerName;
	struct stLocalPlayer*		pLocalPlayer;
	int							iLocalPlayerPing;
	int							iLocalPlayerScore;
	struct stRemotePlayer*		pRemotePlayer[1004];
	int							iIsListed[1004];
	DWORD						dwPlayerIP[1004]; // always 0
};
#pragma pack(pop)
#elif defined(SAMP_R3_COMPILE)
#pragma pack(push, 1)
struct stSAMPPools
{
	//struct MenuPool* menuPool;
	void* pMenuPool;
	struct stActorPool* pActor;
	struct stPlayerPool* pPlayer;
	struct stVehiclePool* pVehicle;
	struct stPickupPool* pPickup;
	struct stObjectPool* pObject;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
};
struct stSAMP
{
public:
	RakPeerInterface* pRakPeerInterface;
private:
	char unk[40];
public:
	RakClientInterface* pRakClientInterface;
	char szIP[257];
	char szHostname[257];
	bool disableCollision;//r3 only
	bool updateCameraTarget;//r3 only
	bool nametagStatus;//r3 only
	uint32_t ulPort;
	BOOL iLanMode;
	uint32_t ulMapIcons[100];
	int iGameState;
	uint32_t ulConnectTick;
	struct stServerPresets* pSettings;
private:
	char unk2[5];
public:
	struct stSAMPPools* pPools;
};
struct stPlayerPool
{
	uint32_t MaxPlayerID;
	struct stRemotePlayer* pRemotePlayer[1004];
	int iIsListed[1004];
	uint32_t prevCollisionFlag[1004];
	int iLocalPlayerPing;
	int iLocalPlayerScore;
	uint16_t sLocalPlayerID;
private:
	int __align;
public:
	//char	szLocalPlayerName[16];
	std::string strLocalPlayerName;
	struct stLocalPlayer* pLocalPlayer;
};
struct stChatEntry
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	DWORD		clTextColor;
	DWORD		clPrefixColor;	// or textOnly colour
};
struct stChatInfo
{
	int					pagesize;
	char* pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			ulUnk0;
	char				logFilePathChatLog[MAX_PATH + 1];
	void* GameUI; // CDXUTDialog
	void* DditBackground; // CDXUTEditBox
	void* DxutScrollBar; // CDXUTScrollBar
	DWORD				clTextColor;
	DWORD				clInfoColor;
	DWORD				clDebugColor;
	DWORD				dwChatboxOffset;
	struct stChatEntry	chatEntry[100];
	void*				m_pFontRenderer;
	void*				m_pChatTextSprite;
	void*				m_pSprite;
	void*				m_pD3DDevice;
	int renderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	void*				m_pD3DRenderToSurface;
	void*				m_pTexture;
	void*				m_pSurface;
	void*				m_pD3DDisplayMode;
private:
	int unk[2];
public:
	int	m_iRedraw;
	int	m_nPrevScrollBarPosition;
	int	m_iFontSizeY;
	int	m_iTimestampWidth;
};
#endif

class Samp
{
private:
	uint32_t dwSAMP_Addr;
	struct stChatInfo* g_Chat = 0;
public:
	struct stSAMP* SAMP;
	Samp::Samp();
	DWORD getBase();
	bool Init();

	void UpdateScoresPingsIps();
	stPlayerPool* GetPlayerPool();
	std::string GetServerIp();
	std::string GetServerName();
	void addMessageToChat(DWORD cColor, char* szMsg, ...);
};

extern Samp* pSamp;