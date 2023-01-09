#include "team_and_conditions.hpp"

namespace CTRPluginFramework {

bool IsMatchTitleId(const std::string& game_title_id) {
  std::string title_id;
  Process::GetTitleID(title_id);
  return game_title_id == title_id;
}

void ReturnNoMatchTitleId() {
  const std::string kMhxTitleId = "0004000000155400";
  const std::string kOtherGameMessage =
      "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。";
  if (!IsMatchTitleId(kMhxTitleId)) {
    MessageBox(kOtherGameMessage).SetClear(ClearScreen::Top)();
    Process::ReturnToHomeMenu();
  }
}

void TeamAndConditionAgreement() {
  const std::string kTeamAndConditionMessageTitle = "利用規約";

  const std::string kTeamAndConditionMessage =
      "①この3gxは無料で提供されます。"
      "もしこのプラグインを購入した場合は、ただちに返金を求めてください。\n"
      "②他人に譲渡する場合、MHX3gxのGithubのリンクを提示すること。\n"
      "③この3gxを使用しデータが破損する等の損害に対して、"
      "ぽんぽこは一切の責任を負いません。\n"
      "利用規約に同意しますか？";

  const std::string kTeamAndConditionAgreementMessage =
      "利用規約に同意する必要があります。";

  if (!MessageBox(kTeamAndConditionMessageTitle, kTeamAndConditionMessage,
                  DialogType::DialogYesNo)
           .SetClear(ClearScreen::Top)()) {
    MessageBox(kTeamAndConditionAgreementMessage).SetClear(ClearScreen::Top)();
    Process::ReturnToHomeMenu();
  }
}

void SkipOpeningMessage() {
  const std::string kAskOpeningMessageSkipMessage =
      "利用規約に同意していただき\n"
      "ありがとうございます。\n"
      "次回からオープニングメッセージを\n"
      "スキップしますか？";

  const std::string kCreatedOpSkipBinMessage = "opskip.binを作成しました。";

  const std::string kEnjoyPluginMessage = "プラグインを楽しんでください！";

  if (MessageBox(kAskOpeningMessageSkipMessage, DialogType::DialogYesNo)
          .SetClear(ClearScreen::Top)()) {
    File::Create("opskip.bin");
    MessageBox(kCreatedOpSkipBinMessage).SetClear(ClearScreen::Top)();
  }
  MessageBox(kEnjoyPluginMessage).SetClear(ClearScreen::Top)();
}

void ShowTeamAndCondition() {
  const std::string kOpeningMessage = "オープニングメッセージ";

  const std::string kThanksMessage =
      "ぽんぽこ @ponpoko094\n"
      "の3gxを使用していただき\n"
      "ありがとうございます。\n"
      "利用規約の同意をお願いします。";

  MessageBox(kOpeningMessage, kThanksMessage).SetClear(ClearScreen::Top)();
  TeamAndConditionAgreement();
  SkipOpeningMessage();
}

void TeamAndCondition() {
  Process::Pause();
  ReturnNoMatchTitleId();
  if (File::Exists("opskip.bin") == 0) {
    ShowTeamAndCondition();
  }
  Process::Play();
}

}  // namespace CTRPluginFramework
