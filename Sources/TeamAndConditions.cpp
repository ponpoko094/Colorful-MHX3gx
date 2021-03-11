#include <string>

#include "TeamAndConditions.hpp"

namespace CTRPluginFramework
{
    void TeamAndCondition()
    {
        static bool file = false;
        std::string titleid;
        std::string openingMessage = "�I�[�v�j���O���b�Z�[�W";

        Process::GetTitleID(titleid);
        if (titleid == "0004000000155400")
        {
            if (!file)
            {
                if (!File::Exists("opskip.bin"))
                {
                    MessageBox(openingMessage, "�ۂ�ۂ� @ponpoko094\n��3gx���g�p���Ă�������\n���肪�Ƃ��������܂��B\n���p�K��̓��ӂ����肢���܂��B")();
                    if (MessageBox(openingMessage, "���p�K��\n�@����3gx�͖����Œ񋟂���܂��B\n�A���l�ɏ��n����ꍇ�AMHX3gx��Github�̃����N��񎦂��邱�ƁB\n�B����3gx���g�p���f�[�^���j�����铙��\n���Q�ɑ΂��āA�ۂ�ۂ��͈�؂̐ӔC�𕉂��܂���B\n�C����3gx�͓��{��MHX\n  (�^�C�g��ID:0004000000155400)\n  �ł̂ݎg�p�ł�����̂Ƃ��܂��B\n���p�K��ɓ��ӂ��܂����H", DialogType::DialogYesNo)())
                    {
                        if (MessageBox(openingMessage, "���p�K��ɓ��ӂ��Ă�������\n���肪�Ƃ��������܂��B\n���񂩂�I�[�v�j���O���b�Z�[�W��\n�X�L�b�v���܂����H", DialogType::DialogYesNo)())
                        {
                            File::Create("opskip.bin");
                            MessageBox(openingMessage, "opskip.bin���쐬���܂����B\n�ݒ��ύX���邽�߂�\n�ċN�������肢���܂��B")();
                            Process::ReturnToHomeMenu();
                        }
                        else
                        {
                            MessageBox(openingMessage, "�v���O�C�����y����ł��������B")();
                        }
                    }
                    else
                    {
                        MessageBox(openingMessage, "���p�K��ɓ��ӂ���K�v������܂��B")();
                        Process::ReturnToHomeMenu();
                    }
                }
                file = true;
            }
        }
        else
        {
            MessageBox(openingMessage, "����3gx�͓��{��MHX(�^�C�g��ID:0004000000155400)�ł̂ݓ��삵�܂��B")();
            Process::ReturnToHomeMenu();
        }
    }
} // namespace CTRPluginFramework