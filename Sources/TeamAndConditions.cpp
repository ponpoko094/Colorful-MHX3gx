#include "TeamAndConditions.hpp"

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

    const std::string teamAndConditionMessage =
        "利用規約\n"
        "①この3gxは無料で提供されます。\n"
        "②他人に譲渡する場合、MHX3gxのGithubのリンクを提示すること。\n"
        "③この3gxを使用しデータが破損する等の\n"
        "損害に対して、ぽんぽこは一切の責任を負いません。\n"
        "④この3gxは日本版MHX\n"
        "(タイトルID:0004000000155400)\n"
        "でのみ使用できるものとします。\n"
        "利用規約に同意しますか？";

    const std::string askOpeningMessageSkipMessage =
        "利用規約に同意していただき\n"
        "ありがとうございます。\n"
        "次回からオープニングメッセージを\n"
        "スキップしますか？";

    const std::string createdOpskipBinMessage =
        "opskip.binを作成しました。\n"
        "設定を変更するために\n"
        "再起動をお願いします。";

    const std::string enjoyPluginMessage = "プラグインを楽しんでください。";

    const std::string teamAndConditionAgreementMessage = "利用規約に同意する必要があります。";

    const std::string otherGameMessage = "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。";

    Process::GetTitleID(titleID);
    if (titleID == mhxTitleID) {
        if (!file) {
            if (!File::Exists(skipSaveFileName)) {
                MessageBox(openingMessage, thanksMessage)();
                if (MessageBox(openingMessage, teamAndConditionMessage, DialogType::DialogYesNo)()) {
                    if (MessageBox(openingMessage, askOpeningMessageSkipMessage, DialogType::DialogYesNo)()) {
                        File::Create(skipSaveFileName);
                        MessageBox(openingMessage, createdOpskipBinMessage)();
                        Process::ReturnToHomeMenu();
                    } else {
                        MessageBox(openingMessage, enjoyPluginMessage)();
                    }
                } else {
                    MessageBox(openingMessage, teamAndConditionAgreementMessage)();
                    Process::ReturnToHomeMenu();
                }
            }
            file = true;
        }
    } else {
        MessageBox(openingMessage, otherGameMessage)();
        Process::ReturnToHomeMenu();
    }
}

}  // namespace CTRPluginFramework