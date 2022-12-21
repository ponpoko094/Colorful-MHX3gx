#include "team_and_conditions.hpp"

namespace CTRPluginFramework {

void TeamAndCondition() {
  std::string title_id;
  const std::string kMhxTitleId = "0004000000155400";

  const std::string kSkipSaveFileName = "opskip.bin";

  const std::string kOpeningMessage = "オープニングメッセージ";

  const std::string kThanksMessage =
      "ぽんぽこ @ponpoko094\n"
      "の3gxを使用していただき\n"
      "ありがとうございます。\n"
      "利用規約の同意をお願いします。";

  const std::string kTeamAndConditionMessageTitle = "利用規約";

  const std::string kTeamAndConditionMessage =
      "①この3gxは無料で提供されます。"
      "もしこのプラグインを購入した場合は、ただちに返金を求めてください。\n"
      "②他人に譲渡する場合、MHX3gxのGithubのリンクを提示すること。\n"
      "③この3gxを使用しデータが破損する等の損害に対して、"
      "ぽんぽこは一切の責任を負いません。\n"
      "利用規約に同意しますか？";

  const std::string kAskOpeningMessageSkipMessage =
      "利用規約に同意していただき\n"
      "ありがとうございます。\n"
      "次回からオープニングメッセージを\n"
      "スキップしますか？";

  const std::string kCreatedOpSkipBinMessage =
      "opskip.binを作成しました。\n"
      "設定を変更するために\n"
      "再起動をお願いします。";

  const std::string kEnjoyPluginMessage = "プラグインを楽しんでください！";

  const std::string kTeamAndConditionAgreementMessage =
      "利用規約に同意する必要があります。";

  const std::string kOtherGameMessage =
      "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。";

  Process::Pause();
  Process::GetTitleID(title_id);
  if (title_id != kMhxTitleId) {
    MessageBox(kOtherGameMessage).SetClear(ClearScreen::Top)();
    Process::ReturnToHomeMenu();
  }
  if (File::Exists(kSkipSaveFileName) == 1) {
    return;
  }
  MessageBox(kOpeningMessage, kThanksMessage).SetClear(ClearScreen::Top)();
  if (!MessageBox(kTeamAndConditionMessageTitle, kTeamAndConditionMessage,
                  DialogType::DialogYesNo)
           .SetClear(ClearScreen::Top)()) {
    MessageBox(kTeamAndConditionAgreementMessage).SetClear(ClearScreen::Top)();
    Process::ReturnToHomeMenu();
  }
  if (!MessageBox(kAskOpeningMessageSkipMessage, DialogType::DialogYesNo)
           .SetClear(ClearScreen::Top)()) {
    MessageBox(kEnjoyPluginMessage).SetClear(ClearScreen::Top)();
    return;
  }
  File::Create(kSkipSaveFileName);
  MessageBox(kCreatedOpSkipBinMessage).SetClear(ClearScreen::Top)();
  Process::Play();
}

}  // namespace CTRPluginFramework
