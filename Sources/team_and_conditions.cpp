#include "team_and_conditions.hpp"

#include <string>

namespace CTRPluginFramework {

void TeamAndCondition() {
  static bool file = false;

  std::string titleID;
  const std::string mhxTitleID = "0004000000155400";

  const std::string skipSaveFileName = "opskip.bin";

  const std::string openingMessage = "オープニングメッセージ";

  const std::string thanksMessage =
      "ぽんぽこ @ponpoko094\n"
      "の3gxを使用していただき\n"
      "ありがとうございます。\n"
      "利用規約の同意をお願いします。";

  const std::string teamAndConditionMessageTitle = "利用規約";

  const std::string teamAndConditionMessage =
      "①この3gxは無料で提供されます。もしこのプラグインを購入した場合は、ただち"
      "に返金を求めてください。\n"
      "②他人に譲渡する場合、MHX3gxのGithubのリンクを提示すること。\n"
      "③この3gxを使用しデータが破損する等の損害に対して、ぽんぽこは一切の責任を"
      "負いません。\n"
      "利用規約に同意しますか？";

  const std::string askOpeningMessageSkipMessage =
      "利用規約に同意していただき\n"
      "ありがとうございます。\n"
      "次回からオープニングメッセージを\n"
      "スキップしますか？";

  const std::string createdOpSkipBinMessage =
      "opskip.binを作成しました。\n"
      "設定を変更するために\n"
      "再起動をお願いします。";

  const std::string enjoyPluginMessage = "プラグインを楽しんでください。";

  const std::string teamAndConditionAgreementMessage =
      "利用規約に同意する必要があります。";

  const std::string otherGameMessage =
      "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。";

  Process::Pause();
  Process::GetTitleID(titleID);
  if (titleID == mhxTitleID) {
    if (!file) {
      if (!File::Exists(skipSaveFileName)) {
        MessageBox(openingMessage, thanksMessage).SetClear(ClearScreen::Top)();
        if (MessageBox(teamAndConditionMessageTitle, teamAndConditionMessage,
                       DialogType::DialogYesNo)
                .SetClear(ClearScreen::Top)()) {
          if (MessageBox(askOpeningMessageSkipMessage, DialogType::DialogYesNo)
                  .SetClear(ClearScreen::Top)()) {
            File::Create(skipSaveFileName);
            MessageBox(createdOpSkipBinMessage).SetClear(ClearScreen::Top)();
            Process::ReturnToHomeMenu();
          } else {
            MessageBox(enjoyPluginMessage).SetClear(ClearScreen::Top)();
          }
        } else {
          MessageBox(teamAndConditionAgreementMessage)
              .SetClear(ClearScreen::Top)();
          Process::ReturnToHomeMenu();
        }
      }
      file = true;
    }
  } else {
    MessageBox(otherGameMessage).SetClear(ClearScreen::Top)();
    Process::ReturnToHomeMenu();
  }
  Process::Play();
}

}  // namespace CTRPluginFramework
