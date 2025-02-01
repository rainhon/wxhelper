#ifndef WXHELPER_WECHAT_FUNCTION_H_
#define WXHELPER_WECHAT_FUNCTION_H_
#include <windows.h>

#include <string>
#include <vector>
namespace wxhelper {
namespace common {
/***************************sqlite3***************************************/
#define SQLITE_OK 0 /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR 1       /* Generic error */
#define SQLITE_INTERNAL 2    /* Internal logic error in SQLite */
#define SQLITE_PERM 3        /* Access permission denied */
#define SQLITE_ABORT 4       /* Callback routine requested an abort */
#define SQLITE_BUSY 5        /* The database file is locked */
#define SQLITE_LOCKED 6      /* A table in the database is locked */
#define SQLITE_NOMEM 7       /* A malloc() failed */
#define SQLITE_READONLY 8    /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT 9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR 10      /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT 11    /* The database disk image is malformed */
#define SQLITE_NOTFOUND 12   /* Unknown opcode in sqlite3_file_control() */
#define SQLITE_FULL 13       /* Insertion failed because database is full */
#define SQLITE_CANTOPEN 14   /* Unable to open the database file */
#define SQLITE_PROTOCOL 15   /* Database lock protocol error */
#define SQLITE_EMPTY 16      /* Internal use only */
#define SQLITE_SCHEMA 17     /* The database schema changed */
#define SQLITE_TOOBIG 18     /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT 19 /* Abort due to constraint violation */
#define SQLITE_MISMATCH 20   /* Data type mismatch */
#define SQLITE_MISUSE 21     /* Library used incorrectly */
#define SQLITE_NOLFS 22      /* Uses OS features not supported on host */
#define SQLITE_AUTH 23       /* Authorization denied */
#define SQLITE_FORMAT 24     /* Not used */
#define SQLITE_RANGE 25      /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB 26     /* File opened that is not a database file */
#define SQLITE_NOTICE 27     /* Notifications from sqlite3_log() */
#define SQLITE_WARNING 28    /* Warnings from sqlite3_log() */
#define SQLITE_ROW 100       /* sqlite3_step() has another row ready */
#define SQLITE_DONE 101      /* sqlite3_step() has finished executing */
/* end-of-error-codes */

#define SQLITE_INTEGER 1
#define SQLITE_FLOAT 2
#define SQLITE_BLOB 4
#define SQLITE_NULL 5
#define SQLITE_TEXT 3

typedef int (*sqlite3_callback)(void *, int, char **, char **);

typedef int(__cdecl *sqlite3_exec)(UINT64,           /* An open database */
                                   const char *sql,  /* SQL to be evaluated */
                                   sqlite3_callback, /* Callback function */
                                   void *,       /* 1st argument to callback */
                                   char **errmsg /* Error msg written here */
);

typedef int(__cdecl *sqlite3_prepare)(
    UINT64 db,          /* Database handle */
    const char *zSql,   /* SQL statement, UTF-8 encoded */
    int nByte,          /* Maximum length of zSql in bytes. */
    UINT64 **ppStmt,    /* OUT: Statement handle */
    const char **pzTail /* OUT: Pointer to unused portion of zSql */
);
typedef int(__cdecl *sqlite3_open)(const char *filename, UINT64 **ppDb);

typedef int(__cdecl *sqlite3_sleep)(int);
typedef int(__cdecl *sqlite3_errcode)(UINT64 *db);
typedef int(__cdecl *sqlite3_close)(UINT64 *);

typedef int(__cdecl *sqlite3_step)(UINT64 *);
typedef int(__cdecl *sqlite3_column_count)(UINT64 *pStmt);
typedef const char *(__cdecl *sqlite3_column_name)(UINT64 *, int N);
typedef int(__cdecl *sqlite3_column_type)(UINT64 *, int iCol);
typedef const void *(__cdecl *sqlite3_column_blob)(UINT64 *, int iCol);
typedef int(__cdecl *sqlite3_column_bytes)(UINT64 *, int iCol);
typedef int(__cdecl *sqlite3_finalize)(UINT64 *pStmt);

/***************************sqlite3  end*************************************/

struct TableInfo {
  char *name;
  INT64 name_len;
  char *table_name;
  INT64 table_name_len;
  char *sql;
  INT64 sql_len;
  char *rootpage;
  INT64 rootpage_len;
};

struct DatabaseInfo {
  UINT64 handle = 0;
  wchar_t *db_name = NULL;
  INT64 db_name_len = 0;
  std::vector<TableInfo> tables;
  INT64 count = 0;
  INT64 extrainfo = 0;
};

struct SqlResult {
  char *column_name;
  INT64 column_name_len;
  char *content;
  INT64 content_len;
  BOOL is_blob;
};

struct InnerMessageStruct {
  char *buffer;
  INT64 length;
  ~InnerMessageStruct() {
    if (this->buffer != NULL) {
      delete[] this->buffer;
      this->buffer = NULL;
    }
  }
};

struct SelfInfoInner {
  std::string name;
  std::string city;
  std::string province;
  std::string country;
  std::string account;
  std::string wxid;
  std::string mobile;
  std::string head_img;
  std::string data_save_path;
  std::string signature;
  std::string current_data_path;
  std::string db_key;
  std::string public_key;
  std::string private_key;
};

struct ContactInner {
  std::string wxid;
  std::string custom_account;
  std::string encrypt_name;
  std::string nickname;
  std::string pinyin;
  std::string pinyin_all;
  DWORD type;
  DWORD verify_flag;
  DWORD reserved1;
  DWORD reserved2;
  ContactInner() {
    wxid = "";
    custom_account = "";
    encrypt_name = "";
    nickname = "";
    pinyin = "";
    pinyin_all = "";
    type = -1;
    verify_flag = -1;
    reserved1 = -1;
    reserved2 = -1;
  }
};

struct ChatRoomInfoInner {
  std::string chat_room_id;
  std::string notice;
  std::string admin;
  std::string xml;
  ChatRoomInfoInner() {
    chat_room_id = "";
    notice = "";
    admin = "";
    xml = "";
  }
};

struct VectorInner {
#ifdef _DEBUG
  INT64 head;
#endif
  INT64 start;
  INT64 finsh;
  INT64 end;
};

struct ChatRoomMemberInner {
  std::string chat_room_id;
  std::string admin;
  std::string admin_nickname;
  std::string member_nickname;
  std::string member;
  ChatRoomMemberInner()
      : chat_room_id(""),
        admin(""),
        admin_nickname(""),
        member_nickname(""),
        member("") {}
};

struct ContactProfileInner {
  std::string wxid;
  std::string account;
  std::string v3;
  std::string nickname;
  std::string head_image;
  ContactProfileInner()
      : wxid(""), account(""), v3(""), nickname(""), head_image("") {}
};

}  // namespace common
namespace V3_9_8_25 {
namespace function {

typedef UINT64 (*__GetAccountService)();
typedef UINT64 (*__GetDataSavePath)(UINT64);
typedef UINT64 (*__GetCurrentDataPath)(UINT64);
typedef UINT64 (*__GetSendMessageMgr)();
typedef UINT64 (*__SendTextMsg)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64,
                                UINT64, UINT64);
typedef UINT64 (*__FreeChatMsg)(UINT64);

typedef UINT64 (*__SendImageMsg)(UINT64, UINT64, UINT64, UINT64, UINT64);
typedef UINT64 (*__NewChatMsg)(UINT64);
typedef UINT64 (*__SendFile)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64,
                             UINT64, UINT64, UINT64, UINT64, UINT64, UINT64);
typedef UINT64 (*__GetAppMsgMgr)();
typedef UINT64 (*__OperatorNew)(UINT64);

typedef UINT64 (*__Free)();
typedef UINT64 (*__GetContactMgr)();
typedef UINT64 (*__GetContactList)(UINT64, UINT64);

typedef UINT64 (*__GetChatRoomMgr)();
typedef UINT64 (*__NewChatRoomInfo)(UINT64);
typedef UINT64 (*__FreeChatRoomInfo)(UINT64);
typedef UINT64 (*__GetChatRoomDetailInfo)(UINT64, UINT64, UINT64, UINT64);
typedef UINT64 (*__DoAddMemberToChatRoom)(UINT64, UINT64, UINT64, UINT64);

typedef UINT64 (*__DoModChatRoomMemberNickName)(UINT64, UINT64, UINT64, UINT64);
typedef UINT64 (*__DoDelMemberFromChatRoom)(UINT64, UINT64, UINT64);
typedef UINT64 (*__GetMemberFromChatRoom)(UINT64, UINT64, UINT64);
typedef UINT64 (*__NewChatRoom)(UINT64);
typedef UINT64 (*__FreeChatRoom)(UINT64);

typedef UINT64 (*__DoTopMsg)(UINT64, UINT64);
typedef UINT64 (*__RemoveTopMsg)(UINT64, UINT64, UINT64);
typedef UINT64 (*__InviteMemberToChatRoom)(UINT64, UINT64, UINT64, UINT64);

typedef UINT64 (*__CreateChatRoom)(UINT64, UINT64, UINT64);
typedef UINT64 (*__QuitChatRoom)(UINT64, UINT64, UINT64);
typedef UINT64 (*__ForwardMsg)(UINT64, UINT64, UINT64, UINT64);

typedef UINT64 (*__GetSNSFirstPage)(UINT64, UINT64, UINT64);
typedef UINT64 (*__GetSNSNextPageScene)(UINT64, UINT64);

typedef UINT64 (*__GetSNSDataMgr)();
typedef UINT64 (*__GetSnsTimeLineMgr)();
typedef UINT64 (*__GetMgrByPrefixLocalId)(UINT64, UINT64);
typedef UINT64 (*__AddFavFromMsg)(UINT64, UINT64);
typedef UINT64 (*__GetChatMgr)();
typedef UINT64 (*__GetFavoriteMgr)();
typedef UINT64 (*__AddFavFromImage)(UINT64, UINT64, UINT64);
typedef UINT64 (*__GetContact)(UINT64, UINT64, UINT64);
typedef UINT64 (*__NewContact)(UINT64);
typedef UINT64 (*__FreeContact)(UINT64);
typedef UINT64 (*__NewMMReaderItem)(UINT64);
typedef UINT64 (*__FreeMMReaderItem)(UINT64);
typedef UINT64 (*__ForwordPublicMsg)(UINT64, UINT64, UINT64);
typedef UINT64 (*__NewAppMsgInfo)(UINT64);
typedef UINT64 (*__FreeAppMsgInfo)(UINT64);
typedef UINT64 (*__ParseAppMsgXml)(UINT64, UINT64, UINT64);
typedef UINT64 (*__GetPreDownLoadMgr)();
typedef UINT64 (*__PushAttachTask)(UINT64, UINT64, UINT64, UINT64);
typedef UINT64 (*__GetCustomSmileyMgr)();
typedef UINT64 (*__SendCustomEmotion)(UINT64, UINT64, UINT64, UINT64, UINT64,
                                      UINT64, UINT64, UINT64);
typedef UINT64 (*__JsApiShareAppMessage)(UINT64);
typedef UINT64 (*__InitJsConfig)(UINT64, UINT64);
typedef UINT64 (*__SendApplet)(UINT64, UINT64, UINT64, UINT64);
typedef UINT64 (*__SendAppletSecond)(UINT64, UINT64, UINT64, UINT64, UINT64,
                                     UINT64);
typedef UINT64 (*__GetAppInfoByWaid)(UINT64, UINT64);
typedef UINT64 (*__CopyShareAppMessageRequest)(UINT64, UINT64);
typedef UINT64 (*__NewWAUpdatableMsgInfo)(UINT64);
typedef UINT64 (*__FreeWAUpdatableMsgInfo)(UINT64);
typedef UINT64 (*__SendPatMsg)(UINT64, UINT64);
typedef UINT64 (*__GetOCRManager)();
typedef UINT64 (*__DoOCRTask)(UINT64, UINT64, UINT64, UINT64, UINT64);


typedef UINT64 (*__GetLockWechatMgr)();
typedef UINT64 (*__RequestLockWechat)(UINT64);
typedef UINT64 (*__RequestUnLockWechat)(UINT64);
typedef UINT64 (*__OnLoginBtnClick)(UINT64);
typedef UINT64 (*__GetQRCodeLoginMgr)();
typedef UINT64 (*__UpdateMsg)(UINT64,UINT64,UINT64);
typedef UINT64 (*__GetVoiceMgr)();
typedef UINT64 (*__ChatMsg2NetSceneSendMsg)(UINT64,UINT64);
typedef UINT64 (*__TranslateVoice)(UINT64,UINT64,UINT64);

}  // namespace function
namespace prototype {

#include <string>
#include <vector>

struct WeChatString {
  wchar_t *ptr;
  DWORD length;
  DWORD max_length;
  INT64 c_ptr = 0;
  DWORD c_len = 0;
  WeChatString() { WeChatString(NULL); }

  WeChatString(const std::wstring &s) {
    ptr = (wchar_t *)(s.c_str());
    length = static_cast<DWORD>(s.length());
    max_length = static_cast<DWORD>(s.length());
  }
  WeChatString(const wchar_t *pStr) { WeChatString((wchar_t *)pStr); }
  WeChatString(int tmp) {
    ptr = NULL;
    length = 0x0;
    max_length = 0x0;
  }
  WeChatString(wchar_t *pStr) {
    ptr = pStr;
    length = static_cast<DWORD>(wcslen(pStr));
    max_length = static_cast<DWORD>(wcslen(pStr));
  }
  void set_value(const wchar_t *pStr) {
    ptr = (wchar_t *)pStr;
    length = static_cast<DWORD>(wcslen(pStr));
    max_length = static_cast<DWORD>(wcslen(pStr) * 2);
  }
};

struct WeChatStr {
  char *ptr;
  INT64 buf;
  INT64 len;
  INT64 maxlen;

  WeChatStr(const char *p) {
    ptr = (char *)p;
    buf = 0;
    len = strlen(p);
    maxlen = len | 0xF;
  }
  WeChatStr() {
    ptr = NULL;
    buf = 0;
    len = 0;
    maxlen = 0xF;
  }
};

}  // namespace prototype
namespace offset {
const UINT64 kGetAccountServiceMgr = 0x94e510;
const UINT64 kSyncMsg = 0xc39680;
const UINT64 kSyncMsgNext = 0xc39680;
const UINT64 kGetCurrentDataPath = 0x101a920;
const UINT64 kGetAppDataSavePath = 0x13a5b90;
const UINT64 kGetSendMessageMgr = 0x94cd10;
const UINT64 kSendTextMsg = 0x1091F70;
const UINT64 kFreeChatMsg = 0x94e590;

const UINT64 kDoAddMsg = 0x10d9450;
const UINT64 kSendImageMsg = 0x1087950;
const UINT64 kChatMsgInstanceCounter = 0x956e00;
const UINT64 kSendFileMsg = 0xea0850;
const UINT64 kGetAppMsgMgr = 0x951cb0;
const UINT64 kGetContactMgr = 0x93a570;
const UINT64 kGetContactList = 0xf6cb70;

const UINT64 k_sqlite3_exec = 0x26e4f20;
const UINT64 k_sqlite3_prepare = 0x26ecaa0;
const UINT64 k_sqlite3_open = 0x27242a0;
const UINT64 k_sqlite3_step = 0x26a8f30;
const UINT64 k_sqlite3_column_count = 0x26a9750;
const UINT64 k_sqlite3_column_name = 0x26aa150;
const UINT64 k_sqlite3_column_type = 0x26a9fa0;
const UINT64 k_sqlite3_column_blob = 0x26a9780;
const UINT64 k_sqlite3_column_bytes = 0x26a9870;
const UINT64 k_sqlite3_finalize = 0x26a7fe0;

const UINT64 kGPInstance = 0x3d8b4f8;
const UINT64 kMicroMsgDB = 0xb8;
const UINT64 kChatMsgDB = 0x2c8;
const UINT64 kMiscDB = 0x5f0;
const UINT64 kEmotionDB = 0x888;
const UINT64 kMediaDB = 0xF48;
const UINT64 kBizchatMsgDB = 0x1AC0;
const UINT64 kFunctionMsgDB = 0x1b98;
const UINT64 kDBName = 0x28;
const UINT64 kStorageStart = 0x0;
const UINT64 kStorageEnd = 0x0;
const UINT64 kMultiDBMgr = 0x3e00910;
const UINT64 kPublicMsgMgr = 0x3dfe098;
const UINT64 kFavoriteStorageMgr = 0x3e01478;

const UINT64 kChatRoomMgr = 0x8e9d30;
const UINT64 kGetChatRoomDetailInfo = 0xe73590;
const UINT64 kNewChatRoomInfo = 0x12006b0;
const UINT64 kFreeChatRoomInfo = 0x1200890;
const UINT64 kDoAddMemberToChatRoom = 0xe63c70;
const UINT64 kDoModChatRoomMemberNickName = 0xe6db00;
const UINT64 kDelMemberFromChatRoom = 0xe64290;
const UINT64 kGetMemberFromChatRoom = 0xe74de0;
const UINT64 kNewChatRoom = 0x11fde50;
const UINT64 kFreeChatRoom = 0x11fe030;

const UINT64 kTopMsg = 0xa5e4f0;
const UINT64 kRemoveTopMsg = 0xe787b0;
const UINT64 kInviteMember = 0xe63650;
const UINT64 kHookLog = 0x1304e60;

const UINT64 kCreateChatRoom = 0xe63340;
const UINT64 kQuitChatRoom = 0xe6e3b0;
const UINT64 kForwardMsg = 0x1091660;

const UINT64 kOnSnsTimeLineSceneFinish = 0x1a73150;
const UINT64 kSNSGetFirstPage = 0x1a51dd0;
const UINT64 kSNSGetNextPageScene = 0x1a77240;
const UINT64 kSNSDataMgr = 0xeebda0;
const UINT64 kSNSTimeLineMgr = 0x19e83a0;
const UINT64 kGetMgrByPrefixLocalId = 0xf0ea60;
const UINT64 kAddFavFromMsg = 0x1601520;
const UINT64 kGetChatMgr = 0x97e4d0;
const UINT64 kGetFavoriteMgr = 0x8c69b0;
const UINT64 kAddFavFromImage = 0x160b920;
const UINT64 kGetContact = 0xf67060;
const UINT64 kNewContact = 0x12e01f0;
const UINT64 kFreeContact = 0x12e08a0;
const UINT64 kNewMMReaderItem = 0x8c79a0;
const UINT64 kFreeMMReaderItem = 0x8c6da0;
const UINT64 kForwordPublicMsg = 0xddc6c0;
const UINT64 kParseAppMsgXml = 0x11b0a70;
const UINT64 kNewAppMsgInfo = 0x91a550;
const UINT64 kFreeAppMsgInfo = 0x8fd1a0;
const UINT64 kGetPreDownLoadMgr = 0x9996f0;
const UINT64 kPushAttachTask = 0x9c0080;
const UINT64 kGetCustomSmileyMgr = 0x915c00;
const UINT64 kSendCustomEmotion = 0xec0a40;
const UINT64 kNewJsApiShareAppMessage = 0x13be1a0;
const UINT64 kInitJsConfig = 0x137bc00;
const UINT64 kSendApplet = 0x13c0920;
const UINT64 kSendAppletSecond = 0x13c1150;
const UINT64 kGetAppInfoByWaid = 0x13c5790;
const UINT64 kCopyShareAppMessageRequest = 0x13c0670;
const UINT64 kNewWAUpdatableMsgInfo = 0x919ca0;
const UINT64 kFreeWAUpdatableMsgInfo = 0x8fc230;
const UINT64 kSendPatMsg = 0x195f340;
const UINT64 kGetOCRManager = 0x999780;
const UINT64 kDoOCRTask = 0x190b2a0;

const UINT64 kGetLockWechatMgr = 0xa727b0;
const UINT64 kRequestLockWechat = 0xa2cc70;
const UINT64 kRequestUnLockWechat = 0xa2cf10;

const UINT64 kOnLoginBtnClick = 0xe0cf70;

const UINT64 kGetQRCodeLoginMgr = 0xdff6d0;

const UINT64 kUpdateMsg = 0xf15c40;
const UINT64 kGetVoiceMgr = 0xbf78f0;
const UINT64 kChatMsg2NetSceneSendMsg = 0x96e8d0;
const UINT64 kTranslateVoice = 0x11217e0;

const UINT64 kLog = 0x13d6bd0;

}  // namespace offset
}  // namespace V3_9_8_15

}  // namespace wxhelper

#endif