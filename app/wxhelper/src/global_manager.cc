#include "global_manager.h"

#include "db.h"
#include "http_url_handler.h"
#include "thread_pool.h"
#include "utils.h"
#include "wechat_service.h"
#include "wxutils.h"
namespace wxhelper {

GlobalManager::~GlobalManager() {}

void GlobalManager::initialize(HMODULE module) {
  state = GlobalContextState::INITIALIZING;
  module_ = module;
  config = std::unique_ptr<Config>(new Config());
  config->Initialize();
  if (config->GetHideDll()) {
    base::utils::HideModule(module);
  }

  UINT64 base = wxutils::GetWeChatWinBase();
  DB::GetInstance().init(base);
  WechatService::GetInstance().SetBaseAddr(base);
  http_server = std::unique_ptr<http::HttpServer>(
      new http::HttpServer(config->GetPort()));
  http_server->AddHttpApiUrl("/api/sendTextMsg", SendTextMsg);
  http_server->AddHttpApiUrl("/api/hookSyncMsg", HookSyncMsg);
  http_server->AddHttpApiUrl("/api/getContactList", GetContacts);
  http_server->AddHttpApiUrl("/api/unhookSyncMsg", UnHookSyncMsg);
  http_server->AddHttpApiUrl("/api/checkLogin", CheckLogin);
  http_server->AddHttpApiUrl("/api/userInfo", GetSelfInfo);
  http_server->AddHttpApiUrl("/api/getDBInfo", GetDBInfo);
  http_server->AddHttpApiUrl("/api/execSql", ExecSql);
  http_server->AddHttpApiUrl("/api/lockWeChat", LockWeChat);
  http_server->AddHttpApiUrl("/api/unlockWeChat", UnLockWeChat);
  http_server->AddHttpApiUrl("/api/clickEnterWeChat", EnterWeChat);
  http_server->AddHttpApiUrl("/api/forwardMsg", ForwardMsg);
  http_server->AddHttpApiUrl("/api/sendImagesMsg", SendImageMsg);
  http_server->AddHttpApiUrl("/api/sendFileMsg", SendFileMsg);
  http_server->AddHttpApiUrl("/api/sendAtText", SendAtText);
  http_server->AddHttpApiUrl("/api/sendMultiAtText", SendMultiAtText);
  http_server->AddHttpApiUrl("/api/getLoginUrl", GetLoginUrl);
  http_server->AddHttpApiUrl("/api/translateVoice", TranslateVoice);
  http_server->AddHttpApiUrl("/api/getTranslateVoiceText", GetTranslateVoiceText);
  http_server->AddHttpApiUrl("/api/hookLog", HookLog);


  http_server->Start();
  base::ThreadPool::GetInstance().Create(2, 8);

  state = GlobalContextState::INITIALIZED;
}

void GlobalManager::finally() {
  if (http_server) {
    http_server->Stop();
  }
}
}  // namespace wxhelper