#include <string>

#include "TeamAndConditions.hpp"

namespace CTRPluginFramework
{
    void TeamAndCondition()
    {
        static bool file = false;
        std::string titleid;
        std::string openingMessage = "オープニングメッセージ";

        Process::GetTitleID(titleid);
        if (titleid == "0004000000155400")
        {
            if (!file)
            {
                if (!File::Exists("opskip.bin"))
                {
                    MessageBox(openingMessage, "ぽんぽこ @ponpoko094\nの3gxを使用していただき\nありがとうございます。\n利用規約の同意をお願いします。")();
                    if (MessageBox(openingMessage, "利用規約\n�@この3gxは無料で提供されます。\n�A他人に譲渡する場合、MHX3gxのGithubのリンクを提示すること。\n�Bこの3gxを使用しデータが破損する等の\n損害に対して、ぽんぽこは一切の責任を負いません。\n�Cこの3gxは日本版MHX\n  (タイトルID:0004000000155400)\n  でのみ使用できるものとします。\n利用規約に同意しますか？", DialogType::DialogYesNo)())
                    {
                        if (MessageBox(openingMessage, "利用規約に同意していただき\nありがとうございます。\n次回からオープニングメッセージを\nスキップしますか？", DialogType::DialogYesNo)())
                        {
                            File::Create("opskip.bin");
                            MessageBox(openingMessage, "opskip.binを作成しました。\n設定を変更するために\n再起動をお願いします。")();
                            Process::ReturnToHomeMenu();
                        }
                        else
                        {
                            MessageBox(openingMessage, "プラグインを楽しんでください。")();
                        }
                    }
                    else
                    {
                        MessageBox(openingMessage, "利用規約に同意する必要があります。")();
                        Process::ReturnToHomeMenu();
                    }
                }
                file = true;
            }
        }
        else
        {
            MessageBox(openingMessage, "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。")();
            Process::ReturnToHomeMenu();
        }
    }
} // namespace CTRPluginFramework