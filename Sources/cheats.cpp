#include "cheats.h"

#include <string>
#include <vector>

namespace CTRPluginFramework {

const std::vector<std::string> listPalicoSkill{
    "なし",
    "体力強化の術【小】",
    "体力強化の術【大】",
    "攻撃強化の術【小】",
    "攻撃強化の術【大】",
    "防御強化の術【小】",
    "防御強化の術【大】",
    "全耐性強化の術",
    "会心強化の術【小】",
    "会心強化の術【大】",
    "匠の術",
    "爆弾強化の術",
    "属性攻撃強化の術",
    "状態異常攻撃強化の術",
    "KOの術",
    "滅気攻撃強化の術",
    "ガード性能の術【小】",
    "ガード性能の術【大】",
    "ガード強化の術",
    "サポート優先の術",
    "サポートプラスの術",
    "サポート行動追加の術",
    "ぶんどり強化の術",
    "復活上手の術",
    "熱・爆弾耐性の術",
    "毒耐性の術",
    "風圧無効の術",
    "麻痺無効の術",
    "気絶無効の術",
    "混乱無効の術",
    "耐震の術",
    "防音の術",
    "睡眠無効の術",
    "細菌学の術",
    "防御力DOWN無効の術",
    "だるま早割りの術",
    "七転八起の術【攻】",
    "七転八起の術【防】",
    "背水の陣の術",
    "怒り発動強化の術",
    "反撃サポート上昇の術",
    "モンスター探知の術",
    "ブーメラン上手の術",
    "罠設置上手の術",
    "採集専門の術",
    "サボりお仕置きの術",
    "体力増加演奏の術",
    "黄金魚狙いの術",
    "最高のネコよ！の術",
    "ハイケイデンスの術",
    "地上最強の術",
    "ゾンビーの術",
    "絶体絶命の術",
    "長飛丸の術",
    "ファナリスの術",
    "エーラの術",
    "遠隔攻撃強化の術",
    "プチタル爆弾改造の術",
    "着こなし上手の術",
    "ユニバーサルの術",
    "きりみ弁当の術",
    "ぐでぐでの術",
    "歌姫の術",
    "風のタクトの術",
    "ランドマスターの術",
    "スーパーキノコの術",
    "あきんどの術",
    "トライフォースの術",
    "モーフボールボムの術",
    "メガフレアの術",
    "防御優先の術",
    "体力強化優先の術",
    "火耐性強化の術",
    "水耐性強化の術",
    "雷耐性強化の術",
    "氷耐性強化の術",
    "龍耐性強化の術",
    "透明",
};

std::vector<std::string> listPalicoAction{
    "なし",
    "薬草笛の技",
    "回復笛の技",
    "真・回復笛の技",
    "解毒・消臭笛の技",
    "応援笛の技",
    "鬼人笛の技",
    "硬化笛の技",
    "超音波笛の技",
    "プチタル爆弾の技",
    "小タル爆弾の技",
    "大タル爆弾の技",
    "大タル爆弾Gの技",
    "特大タル爆弾の技",
    "打ち上げタル爆弾の技",
    "閃光爆弾の技",
    "設置型爆弾の技",
    "設置型爆弾Gの技",
    "落とし穴の技",
    "シビレ罠の技",
    "毒々落とし穴の技",
    "トランポリンの技",
    "ネコ式活力壺の技",
    "回復贈物の技",
    "緊急撤退の技",
    "巨大ブーメランの技",
    "貫通ブーメランの技",
    "隠密防御の技",
    "武器強化の技",
    "憤怒の技",
    "挑発の技",
    "オトモ鼓舞の技",
    "こやし玉の技",
    "応援ダンスの技",
    "治・ローリングの技",
    "爆・ローリングの技",
    "ぶんどりの技",
    "遠隔ぶんどりの技",
    "ネコまっしぐらの技",
    "ネコ爪乱舞の技",
    "しこ踏みドンの技",
    "イガグリ大砲の技",
    "電転虫発射の技",
    "ここ掘れニャンの技",
    "メガブーメランの技",
    "ネコ式火竜車の技",
    "透明",
};

StringVector listToggle{
    "はい",
    "いいえ",
};

// スーパーノヴァ連射等
void NoMotion(MenuEntry *entry) {
  KeyboardPlus::Toggle32("モーションを無くしますか？", 0xAF55A8, 0xE3A00001,
                         0x13A00001);
}

// クエスト時間停止
void QuestTimeStop(MenuEntry *entry) {
  KeyboardPlus::Toggle32("クエスト時間を停止しますか？", 0x90E5BC, 0xEA000008,
                         0xBA000008);
}

// 名前変更
void HunterNameChange(MenuEntry *entry) {
  StringVector listFixKeyboard{"定型文", "キーボード"};
  std::string hunterNameFix, hunterNameNow, hunterNameKeyboard;
  Process::ReadString(0x83AE380, hunterNameFix, 0x1E, StringFormat::Utf8);
  Process::ReadString(0x831B72A, hunterNameNow, 0x1E, StringFormat::Utf8);
  Keyboard keyboard("どちらで変更しますか？\n現在の名前[" + hunterNameNow + "]",
                    listFixKeyboard);
  int choice = keyboard.Open();
  if (choice == 0) {
    for (int i = 0; i < 8; i++) {
      Process::Write32(i * 4 + 0x831B72A, 0);
    }
    Process::WriteString(0x831B72A, hunterNameFix, StringFormat::Utf8);
  }
  if (choice == 1) {
    Keyboard keyboard("名前を入力してください。");
    keyboard.Open(hunterNameKeyboard);
    for (int i = 0; i < 8; i++) {
      Process::Write32(i * 4 + 0x831B72A, 0);
    }
    Process::WriteString(0x831B72A, hunterNameKeyboard, StringFormat::Utf8);
  }
}

// 障害物無視
void WallThrough(MenuEntry *entry) {
  KeyboardPlus::Toggle32("障害物無視しますか？", 0x3246F4, 0xEA00001E,
                         0x0A00001E);
}

// ハンターランク変更
void HunterRankChange(MenuEntry *entry) {
  u16 hr;
  Process::Read16(0x831B76A, hr);
  Keyboard keyboard(
      Utils::Format("ハンターランクを入力してください\n現在[%u]", hr));
  keyboard.IsHexadecimal(false);
  keyboard.Open(hr);
  Process::Write16(0x831B76A, hr);
}

// モンスターワンパンキル
void OneAttackKill(MenuEntry *entry) {
  KeyboardPlus::Toggle32("瞬殺しますか？", 0x8CF54C, 0xE3A01000, 0xE0911003);
}

// 宙に浮くバグ
void FloatBug(MenuEntry *entry) {
  Process::Write32(0xC01414, 0xE51F000C);
  Process::Write32(0xC01418, 0xE5860040);
  Process::Write32(0xC0141C, 0xED960A10);
  Process::Write32(0xC01420, 0xE12FFF1E);
  Process::Write32(0xC01424, 0xE51F001C);
  Process::Write32(0xC01428, 0xE5860040);
  Process::Write32(0xC0142C, 0xE3A00000);
  Process::Write32(0xC01430, 0xE12FFF1E);
  Process::Write32(0x2F7BA4, 0xEB24261E);
  Process::Write32(0x30A2AC, 0xEB23DC58);
  if (Controller::IsKeysPressed(L + Select)) {
    Process::WriteFloat(0xC01410, 2);
  }
  if (Controller::IsKeysPressed(R + Select)) {
    Process::WriteFloat(0xC01410, 1);
  }
}

// 属性
void AttributePointChange(MenuEntry *entry) {
  u16 attributePoint;
  Keyboard keyboard("属性値を入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(attributePoint);
  Process::Write16(0x831B45A, attributePoint);
}

// ゼニー
void MoneyChange(MenuEntry *entry) {
  u32 money;
  Keyboard keyboard("所持金を入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(money);
  Process::Write32(0x83B3818, money);
}

// ポイント
void WycademyPointChange(MenuEntry *entry) {
  u32 wycademyPoint;
  Keyboard keyboard("龍歴員ポイントを入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(wycademyPoint);
  Process::Write32(0x83B3820, wycademyPoint);
}

// 全狩技開放
void HunterArtRelease(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0xDD9F30, offset);
  Process::Write32(offset + 0x9E0, 0xFFFFFFFE);
  Process::Write32(offset + 0x9E4, 0x00FFFFFF);
  Process::Write32(offset + 0x9E8, 0xFFFFFFFE);
  Process::Write32(offset + 0x9EC, 0xFFFFFFFF);
  Process::Write32(offset + 0x9F0, 0x0003FFFF);
}

// 採取無限
void InfiniteCollect(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("採取無限にしますか？",
                              {
                                  {0x847594, 0xE2400000, 0xE2400001},
                                  {0x847684, 0xE2400000, 0xE2400001},
                                  {0x8CD544, 0xE3A00000, 0xEBFF5F26},
                              });
}

// 素材なしで調合可能
void NoMaterialCompound(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("素材無しで調合可能にしますか？",
                              {
                                  {0x39D88C, 0xE3A00000, 0xE12FFF32},
                                  {0xA0ADCC, 0xE3A00000, 0xEB01A495},
                              });
}

// 素材無しで装備作成可能
void NoMaterialEquipmentCreate(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("素材無しで装備作成可能にしますか？",
                              {
                                  {0x18587C, 0xE3A00063, 0xE0800004},
                                  {0x18644C, 0xE3A00001, 0xA3A00001},
                                  {0x41AbA8, 0xE3A00001, 0xEB1B2B79},
                                  {0x421AB0, 0xE3A00001, 0xEB1B0FB7},
                              });
}

// スタミナ無限
void InfiniteStamina(MenuEntry *entry) {
  KeyboardPlus::Toggle32("スタミナ無限にしますか？", 0xA87104, 0xE3A00001,
                         0xE12FFF32);
}

// 常にマップ表示
void AlwaysDisplayMap(MenuEntry *entry) {
  KeyboardPlus::Toggle32("常にマップ表示しますか？", 0x2CFF30, 0xE3A00001,
                         0xEB207503);
}

// 常にモンスターペイント
void AlwaysPaint(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("常にモンスターペイントしますか？",
                              {
                                  {0x39CEB0, 0xE3A00001, 0xEB1D4123},
                                  {0x8ECBB4, 0xE3A00001, 0xD3A00000},
                              });
}

// 会心率100パーセント
void CriticalRate100(MenuEntry *entry) {
  KeyboardPlus::Toggle32("会心率を100％にしますか？", 0x8F3150, 0xE3A000C8,
                         0xEB07E80A);
}

// 狩技無限
void InfiniteHunterArt(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("狩技を無限にしますか？",
                              {
                                  {0xA89F70, 0xE92D0001, 0xE19320F2},
                                  {0xA89F74, 0xE1DC00F2, 0xE1DC30F2},
                                  {0xA89F78, 0xE18300B2, 0xE1520003},
                                  {0xA89F7C, 0xE8BD0001, 0xAA000001},
                                  {0xA89F80, 0xEA000000, 0xE3A00000},
                              });
}

// ボウガンオートリロード
void BowgunAutoReload(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("ボウガン自動装填しますか？",
                              {
                                  {0x324984, 0xE5C405AA, 0xE1A02C23},
                                  {0x32498C, 0xE5C405AB, 0xE5C425AB},
                              });
}

// HP無限
void InfiniteHP(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("HP無限にしますか？",
                              {
                                  {0x46C37C, 0xE1D025F4, 0xE1D025F2},
                                  {0x46C398, 0xE1C025B2, 0xE1D025F4},
                              });
}

// 斬れ味無限
void InfiniteSharpness(MenuEntry *entry) {
  KeyboardPlus::Toggle32("斬れ味無限にしますか？", 0x35B270, 0xE5901218,
                         0xE0811004);
}

// ボウガンの弾、アイテム無限
void InfiniteItemAmmo(MenuEntry *entry) {
  KeyboardPlus::Toggle32("アイテム&弾丸を無限にしますか？", 0x35C658,
                         0xE3A07000, 0xE1A07002);
}

// 溜め最大
void ChargeGageMax(MenuEntry *entry) {
  KeyboardPlus::Toggle32("チャージゲージ最大にしますか？", 0x32D004, 0xE3A01064,
                         0xE0811005);
}

// 運搬物をポーチに入れる
void CargoPutInPorch(MenuEntry *entry) {
  KeyboardPlus::Toggle32("運搬物をポーチに入れますか？", 0xAE5488, 0x93A00000,
                         0x93A00001);
}

// 常に3つ狩技装着可能
void Always3HunterArtEquip(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("常に3つ狩技装着可能にしますか？",
                              {
                                  {0xAF8C0C, 0xE3A00003, 0xE3510000},
                                  {0xAF8C10, 0xE12FFF1E, 0xE3A00000},
                              });
}

// スーパーアーマー
void SuperArmor(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("スーパーアーマーにしますか？",
                              {
                                  {0x322C60, 0xE3A05001, 0xE4A05000},
                                  {0x3322F0, 0xE3A00001, 0xE3A00000},
                              });
}

// アイテムボックス1400枠拡張
void ItemBox1400Expansion(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("アイテムボックス1400枠拡張しますか？",
                              {
                                  {0x9F1AB0, 0xE5901734, 0xE5900734},
                                  {0x9F1AB4, 0xE3811606, 0xE3100602},
                                  {0x9F1AB8, 0xE5801734, 0x13A01001},
                                  {0x9F1ABC, 0xE3A01002, 0xE3100501},
                                  {0x9F1AC0, 0xE1A00000, 0x12811001},
                              });
}

// 装備欄開放
void EquipmentAllRelease(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("装備欄開放しますか？",
                              {
                                  {0xB0832C, 0xE3A00001, 0x13A00001},
                                  {0xB0825C, 0xE3A00001, 0x13A00001},
                                  {0xAE59AC, 0xE3A00001, 0x13A00001},
                              });
}

// 無敵
void Invincible(MenuEntry *entry) {
  KeyboardPlus::Toggle32("無敵にしますか？", 0xA2E3D0, 0xE3A00000, 0xE3A00001);
}

// 斬れ味レベル+2
void SharpnessPlus2(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("斬れ味レベル+2にしますか？",
                              {
                                  {0x4F5954, 0xE1A00000, 0x0A000010},
                                  {0xC18EF4, 0xE3510053, 0x00000000},
                                  {0xC18EF8, 0x03A00001, 0x00000000},
                                  {0xC18EFC, 0xE12FFF1E, 0x00000000},
                                  {0xAED3D0, 0xEA04AEC7, 0xE3500000},
                              });
}

// 全アイテム販売
void AllItemSold(MenuEntry *entry) {
  KeyboardPlus::MultiToggle32("全アイテム販売しますか？",
                              {
                                  {0x2A124C, 0xE3A01E7A, 0xE1A01006},
                                  {0x2A184C, 0xE08A9007, 0xE0860080},
                                  {0x2A1854, 0xE2899001, 0xE1D090BE},
                                  {0x2A1868, 0xE08A1007, 0xE1D110BE},
                              });
}

// サポートゲージ無限
void ProwlerSupportGageMax(MenuEntry *entry) {
  u32 offset, cmp32;
  Process::Read32(0xDD5348, offset);
  if (Process::Read32(offset + 0x14, cmp32) && cmp32 != 0x0) {
    Process::Read32(offset + 0x14, offset);
    Process::Write16(offset + 0x2220, 0x384);
  }
}

// アイテムを99個まで持てる
void HaveItem99(MenuEntry *entry) {
  int choice = KeyboardPlus::LengthToggle32(
      "アイテムを99個まで持ちますか？", 24, 0xC18DB0,
      {0xE5C50021, 0xE92D4007, 0xE59F0044, 0xE5900000, 0xE5900014, 0xE5900068,
       0xE5901000, 0xE59F2034, 0xE1510002, 0x18BD8007, 0xE5D0100E, 0xE3510001,
       0x18BD8007, 0xE280000E, 0xE59F101C, 0xE0811000, 0xE3A02063, 0xE4C02038,
       0xE1510000, 0x1AFFFFFC, 0xE8BD8007, 0x00DD41B8, 0x00DA0CA8, 0x0001AA58});
  if (choice == 0) {
    Process::Write32(0x31689C, 0xEB240943);
  }
  if (choice == 1) {
    Process::Write32(0x31689C, 0xE5C50021);
  }
}

// 溜め高速化
void ChargeSpeedUp(MenuEntry *entry) {
  int choice = KeyboardPlus::LengthToggle32(
      "溜め高速化しますか？", 11, 0xC18E24,
      {0xE24F0000, 0xEAF96EC2, 0xE92D0002, 0xE59F1014, 0xE151000E, 0x024F0014,
       0xEDD01A07, 0xE8BD0002, 0xEAF96EC2, 0x41200000, 0x0156B438});
  if (choice == 0) {
    Process::Write32(0x0A74950, 0xEA069135);
    Process::Write32(0x0326228, 0xEA23CAFD);
  }
  if (choice == 1) {
    Process::Write32(0x0A74950, 0xEDD01A07);
    Process::Write32(0x0326228, 0xEA1D39C2);
  }
}

static float playerSpeed = 1;
void PlayerSpeedOption(MenuEntry *entry) {
  std::vector<std::string> list1to10Magnification{
      "1倍", "2倍", "3倍", "4倍", "5倍", "6倍", "7倍", "8倍", "9倍", "10倍"};

  Keyboard keyboard("速度を何倍にしますか？", list1to10Magnification);
  int choice = keyboard.Open();
  playerSpeed = choice + 1;
}

// 速度変更
void PlayerSpeedChange(MenuEntry *entry) {
  Process::Write32(0xC18D80, 0xED9F1A04);
  Process::Write32(0xC18D84, 0xED9F2A04);
  Process::Write32(0xC18D88, 0xEE311A02);
  Process::Write32(0xC18D8C, 0xEE000A01);
  Process::Write32(0xC18D90, 0xE1A00004);
  Process::Write32(0xC18D94, 0xE12FFF1E);
  Process::Write32(0xC18D98, 0xBF800000);
  Process::WriteFloat(0xC18D9C, playerSpeed);
  Process::Write32(0xC18DA0, 0xE51F000C);
  Process::Write32(0xC18DA4, 0xE5860040);
  Process::Write32(0xC18DA8, 0xE3A00000);
  Process::Write32(0xC18DAC, 0xE12FFF1E);
  Process::Write32(0x316898, 0xEB240940);
  Process::Write32(0x320534, 0xEB23E211);
  if (Controller::IsKeysPressed(L + Select)) {
    Process::WriteFloat(0xC18D9C, playerSpeed);
    OSD::Notify("Speed:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(R + Select)) {
    Process::WriteFloat(0xC18D9C, 1);
    OSD::Notify("Speed:" << Color::Red << "OFF!");
  }
}

static u8 playerAttackPowerMagnification = 0x1;
// 攻撃力倍率変更設定
void PlayerAttackPowerMagnificationOption(MenuEntry *entry) {
  Keyboard keyboard("攻撃力を何倍にしますか?\n1~255の間");
  keyboard.IsHexadecimal(false);
  keyboard.Open(playerAttackPowerMagnification);
}

// 攻撃力変更
void PlayerAttackPowerMagnificationChange(MenuEntry *entry) {
  Process::Write32(0xC18E50, 0xE3A01000);
  Process::Write32(0xC18E54, 0xE92D4018);
  Process::Write32(0xC18E58, 0xE3A04001);
  Process::Write32(0xC18E5C, 0xE1D232B2);
  Process::Write32(0xC18E60, 0xE0030493);
  Process::Write32(0xC18E64, 0xE3530C7D);
  Process::Write32(0xC18E68, 0xA3A03C7D);
  Process::Write32(0xC18E6C, 0xE1C232B2);
  Process::Write32(0xC18E70, 0xE8BD8018);
  Process::Write32(0x8F1B84, 0xEB0C9CB1);
  if (Controller::IsKeysPressed(Y + DPadUp)) {
    Process::Write32(0xC18E58, 0xE3A04000 + playerAttackPowerMagnification);
    OSD::Notify("Attack:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(Y + DPadDown)) {
    Process::Write32(0xC18E58, 0xE3A04001);
    OSD::Notify("Attack:" << Color::Red << "OFF!");
  }
}

static u8 playerDefencePowerMagnification = 0x1;
// 防御力倍率変更設定
void PlayerDefencePowerMagnificationOption(MenuEntry *entry) {
  Keyboard keyboard("防御力を何倍にしますか?\n1~255の間");
  keyboard.IsHexadecimal(false);
  keyboard.Open(playerDefencePowerMagnification);
}

// 防御力変更
void playerDefencePowerMagnificationChange(MenuEntry *entry) {
  if (Controller::IsKeysPressed(X + DPadUp)) {
    Process::Write32(0x0C18E80, 0xE92D4004);
    Process::Write8(0x0C18E84, playerDefencePowerMagnification);
    Process::Write8(0x0C18E85, 0x20);
    Process::Write16(0x0C18E86, 0xE3A0);
    Process::Write32(0x0C18E88, 0xE0000290);
    Process::Write32(0x0C18E8C, 0xE3500C7D);
    Process::Write32(0x0C18E90, 0xA3A00C7D);
    Process::Write32(0x0C18E94, 0xE18100B5);
    Process::Write32(0x0C18E98, 0xE8BD8004);
    Process::Write32(0x08F2AC4, 0xEB0C98ED);
    OSD::Notify("Defence:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(X + DPadDown)) {
    Process::Write32(0x0C18E80, 0xE92D4004);
    Process::Write8(0x0C18E84, 0x1);
    Process::Write8(0x0C18E85, 0x20);
    Process::Write16(0x0C18E86, 0xE3A0);
    Process::Write32(0x0C18E88, 0xE0000290);
    Process::Write32(0x0C18E8C, 0xE3500C7D);
    Process::Write32(0x0C18E90, 0xA3A00C7D);
    Process::Write32(0x0C18E94, 0xE18100B5);
    Process::Write32(0x0C18E98, 0xE8BD8004);
    Process::Write32(0x08F2AC4, 0xEB0C98ED);
    OSD::Notify("Defence:" << Color::Red << "OFF!");
  }
}

// 肌の色変更
void SkinColorChange(MenuEntry *entry) {
  std::vector<std::string> listSkinColor{
      "赤色", "橙色", "黄色", "黄緑", "緑色", "緑水", "水色",
      "水青", "青色", "紫色", "紫桃", "白色", "灰色", "黒色",
  };

  std::vector<u32> listSkinColorHex{
      0x000000FF, 0x000080FF, 0x0000FFFF, 0x0000FF80, 0x0000FF00,
      0x0080FF00, 0x00FFFF00, 0x00FF8000, 0x00FF0000, 0x00FF0080,
      0x00FF00FF, 0x008000FF, 0x00FFFFFF, 0x00808080, 0x00000000,
  };

  Keyboard keyboard("肌の色を何色にしますか？", listSkinColor);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write32(0x831B70C, listSkinColorHex[choice]);
  }
}

// 肌の色R設定
void SkinRedChange(MenuEntry *entry) {
  u8 r;
  Keyboard keyboard("赤の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  keyboard.Open(r);
  Process::Write8(0x831B70C, r);
}

// 肌の色G設定
void SkinGreenChange(MenuEntry *entry) {
  u8 g;
  Keyboard keyboard("緑の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(g) != -1) {
    Process::Write8(0x831B70D, g);
  }
}

// 肌の色B設定
void SkinBlueChange(MenuEntry *entry) {
  u8 b;
  Keyboard keyboard("青の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(b) != -1) {
    Process::Write8(0x831B70E, b);
  }
}

static u8 palicoAttack = 0x1;
// ニャンター攻撃力変更
void PalicoAttackPowerMagnificationChange(MenuEntry *entry) {
  u32 data32, cmp32;
  if (Controller::IsKeysPressed(Y + DPadUp)) {
    Process::Write32(0xC18F80, 0xE92D400C);
    Process::Write8(0xC18F84, palicoAttack);
    Process::Write8(0xC18F85, 0x30);
    Process::Write16(0xC18F86, 0xE3A0);
    Process::Write32(0xC18F88, 0xE1D522B2);
    Process::Write32(0xC18F8C, 0xE0020392);
    Process::Write32(0xC18F90, 0xE3520C7D);
    Process::Write32(0xC18F94, 0xA3A02C7D);
    Process::Write32(0xC18F98, 0xE1C522B2);
    Process::Write32(0xC18F9C, 0xE1D523BA);
    Process::Write32(0xC18FA0, 0xE0020392);
    Process::Write32(0xC18FA4, 0xE3520C7D);
    Process::Write32(0xC18FA8, 0xA3A02C7D);
    Process::Write32(0xC18FAC, 0xE1C523BA);
    Process::Write32(0xC18FB0, 0xE3A01010);
    Process::Write32(0xC18FB4, 0xE8BD800C);
    Process::Write32(0xC18FB8, 0x00000005);
    Process::Write32(0x8F4198, 0xEB0C9378);
    Process::Write32(0x5D60BC, 0xEA000002);
    OSD::Notify("Prowler Attack:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(Y + DPadDown)) {
    Process::Write32(0xC18F80, 0xE92D400C);
    Process::Write8(0xC18F84, 0x1);
    Process::Write8(0xC18F85, 0x30);
    Process::Write16(0xC18F86, 0xE3A0);
    Process::Write32(0xC18F88, 0xE1D522B2);
    Process::Write32(0xC18F8C, 0xE0020392);
    Process::Write32(0xC18F90, 0xE3520C7D);
    Process::Write32(0xC18F94, 0xA3A02C7D);
    Process::Write32(0xC18F98, 0xE1C522B2);
    Process::Write32(0xC18F9C, 0xE1D523BA);
    Process::Write32(0xC18FA0, 0xE0020392);
    Process::Write32(0xC18FA4, 0xE3520C7D);
    Process::Write32(0xC18FA8, 0xA3A02C7D);
    Process::Write32(0xC18FAC, 0xE1C523BA);
    Process::Write32(0xC18FB0, 0xE3A01010);
    Process::Write32(0xC18FB4, 0xE8BD800C);
    Process::Write32(0xC18FB8, 0x00000005);
    Process::Write32(0x8F4198, 0xEB0C9378);
    Process::Write32(0x5D60BC, 0xEA000002);
    OSD::Notify("Prowler Attack:" << Color::Red << "OFF!");
  }
  if (Process::Read32(0xC18FB8, cmp32) && cmp32 != 0x0) {
    Process::Read32(0xC18FB8, data32);
    data32 += 0xFFFFFFFF;
    Process::Write32(0xC18FB8, data32);
  }
  if (Process::Read32(0xC18FB8, cmp32) && cmp32 == 0x1) {
    Process::Write32(0x5D60BC, 0x0A000002);
  }
}

// ニャンター攻撃力変更設定
void PalicoAttackPowerMagnificationOption(MenuEntry *entry) {
  Keyboard keyboard("防御力を何倍にしますか?\n1~255の間");
  keyboard.IsHexadecimal(false);
  keyboard.Open(palicoAttack);
}

static u8 palicoDefence = 0x1;
// ニャンター防御力変更
void PalicoDefencePowerMagnificationChange(MenuEntry *entry) {
  u32 offset, data32, cmp32;
  if (Controller::IsKeysPressed(X + DPadUp)) {
    Process::Write32(0xC18FE0, 0xE92D4004);
    Process::Write8(0xC18FE4, palicoDefence);
    Process::Write8(0xC18FE5, 0x20);
    Process::Write16(0xC18FE6, 0xE3A0);
    Process::Write32(0xC18FE8, 0xE0000290);
    Process::Write32(0xC18FEC, 0xE3500C7D);
    Process::Write32(0xC18FF0, 0xA3A00C7D);
    Process::Write32(0xC18FF4, 0xE18100B5);
    Process::Write32(0xC18FF8, 0xE8BD8004);
    Process::Write32(0x8F4C1C, 0xEB0C90EF);
    Process::Write32(0xC18FFC, 0x00000005);
    Process::Write32(0x5D60BC, 0xEA000002);
    OSD::Notify("Prowler Defence:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(X + DPadDown)) {
    Process::Write8(0xC18FE4, 0x01);
    OSD::Notify("Prowler Defence:" << Color::Red << "OFF!");
  }
  if (Process::Read32(0xC18FFC, cmp32) && cmp32 != 0x0) {
    Process::Read32(0xC18FFC, data32);
    data32 += 0xFFFFFFFF;
    Process::Write32(0xC18FFC, data32);
  }
  offset = 0x00000000;
  if (Process::Read32(0xC18FFC, cmp32) && cmp32 == 0x1) {
    Process::Write32(0x5D60BC, 0xA000002);
  }
}

// ニャンター防御力変更設定
void PalicoDefencePowerMagnificationOption(MenuEntry *entry) {
  Keyboard keyboard("防御力を何倍にしますか?\n1~255の間");
  keyboard.IsHexadecimal(false);
  keyboard.Open(palicoDefence);
}

// 画面にパス表示
void DisplayBasePassword(MenuEntry *entry) {
  static int addressOn = 0;
  static u16 pass;
  u16 online;
  addressOn = true;
  Process::Read16(0xE2251C, pass);
  Process::Read16(0x80913EC, online);

  if (online == 0x100) {
    addressOn = true;
    OSD::Run([](const Screen &screen) {
      if (!screen.IsTop) {
        return (false);
      }
      if (addressOn == true) {
        if (pass <= 9999) {
          if (pass <= 999) {
            screen.Draw(Utils::Format("Pass 0%u", pass), 10, 80, Color::Yellow);
            addressOn = false;
          } else {
            screen.Draw(Utils::Format("Pass %u", pass), 10, 80, Color::Yellow);
            addressOn = false;
          }
        }
      }
      return (true);
    });
  } else {
    addressOn = false;
  }
}

// ガンランス弾無限
void GunlanceAmmoInfinite(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write8(offset + 0x1922, 0xFF);
}

// ガンランスオーバーヒート無効
void GunlanceInvalidOverHeat(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write32(offset + 0x1FF8, 0x0);
}

static u16 heat;
// ヒートゲージ変更
void GunlanceHeatGageOption(MenuEntry *entry) {
  Keyboard keyboard(
      "固定したい値を決めてください。\n0:最小\n4D:橙\nD4:赤\n12C:最大");
  keyboard.Open(heat);
}

// ガンランスヒートゲージ固定
void GunlanceHeatGageFix(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write16(offset + 0x2018, heat);
}

// 護石作成
void AmuletCreate(MenuEntry *entry) {
  Keyboard keyboard("護石を作成しますか？", listToggle);
  int choice = keyboard.Open();
  if (choice == 0) {
    Process::Write8(0x8386D78, 0x6);
    Process::Write8(0x8386D7A, 0x1);
    Process::Write16(0x8386D8E, 0x147);
  }
}

// 護石種類変更
void AmuletTypeChange(MenuEntry *entry) {
  std::vector<std::string> listAmuletType{
      "表示無し", "兵士の護石", "闘士の護石", "騎士の護石",
      "城塞の護石", "女王の護石", "王の護石", "龍の護石"};

  Keyboard keyboard("護石の種類を選んでください", listAmuletType);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(0x8386D7A, choice);
  }
}

// 護石スキル変更
void AmuletSkillChange(MenuEntry *entry) {
  std::vector<std::string> listAmuletSkill{
      "スキル無し", "毒", "麻痺", "睡眠", "気絶",
      "聴覚保護", "風圧", "耐震", "だるま", "耐暑",
      "耐寒", "寒冷適応", "炎熱適応", "盗み無効", "対防御DOWN",
      "狂撃耐性", "細菌学", "裂傷", "攻撃", "防御",
      "体力", "火耐性", "水耐性", "雷耐性", "氷耐性",
      "龍耐性", "属性耐性", "火属性攻撃", "水属性攻撃", "雷属性攻撃",
      "氷属性攻撃", "龍属性攻撃", "属性攻撃", "特殊攻撃", "研ぎ師",
      "匠", "斬れ味", "剣術", "研磨術", "鈍器",
      "抜刀会心", "抜刀滅気", "納刀", "装填速度", "反動",
      "精密射撃", "通常弾強化", "貫通弾強化", "散弾強化", "重撃弾強化",
      "通常弾追加", "貫通弾追加", "散弾追加", "榴弾追加", "拡散弾追加",
      "毒瓶追加", "麻痺瓶追加", "睡眠瓶追加", "強撃瓶追加", "属強瓶追加",
      "接撃瓶追加", "滅気瓶追加", "爆破瓶追加", "速射", "射法",
      "装填数", "変則射撃", "弾薬節約", "達人", "痛撃",
      "連撃", "特殊会心", "属性会心", "会心強化", "溜め短縮",
      "スタミナ", "体術", "気力回復", "回避性能", "回避距離",
      "泡沫", "ガード性能", "ガード強化", "KO", "滅気攻撃",
      "笛", "砲術", "重撃", "爆弾強化", "本気",
      "闘魂", "無傷", "チャンス", "底力", "逆境",
      "逆上", "窮地", "根性", "気配", "采配",
      "号令", "乗り", "跳躍", "無心", "千里眼",
      "観察眼", "狩人", "運搬", "加護", "英雄の盾",
      "回復量", "回復速度", "効果持続", "広域", "腹減り",
      "食いしん坊", "食事", "節食", "肉食", "茸食",
      "野草知識", "調合成功率", "調合数", "高速設置", "採取",
      "ハチミツ", "護石王", "気まぐれ", "運気", "剥ぎ取り",
      "捕獲", "ベルナ", "ココット", "ポッケ", "ユクモ",
      "紅兜", "大雪主", "矛砕", "岩穿", "紫毒姫",
      "宝纏", "白疾風", "隻眼", "黒炎王", "金雷公",
      "荒鉤爪", "燼滅刃", "北辰納豆流", "胴系統倍加"};

  Keyboard keyboard("どちらのスキルを変更しますか？",
                    {"第一スキル", "第二スキル"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard("第一スキルを選んでください", listAmuletSkill);
    if (int choice = keyboard.Open() != -1) {
      Process::Write8(0x8386D88, choice);
    }
  }
  if (choice == 1) {
    Keyboard keyboard("第二スキルを選んでください", listAmuletSkill);
    if (int choice = keyboard.Open() != -1) {
      Process::Write8(0x8386D89, choice);
    }
  }
}

// 護石スキルポイント変更
void AmuletSkillPointChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("どちらのスキルポイントを変更しますか？");
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard(
        "第一スキルポイントを入力してください\n+127~-"
        "128ポイントまで指定できます。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(a) != -1) {
      Process::Write8(0x8386D8A, a);
    }
  }
  if (choice == 1) {
    Keyboard keyboard(
        "第二スキルポイントを入力してください\n+127~-"
        "128ポイントまで指定できます。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(a) != -1) {
      Process::Write8(0x8386D8B, a);
    }
  }
}

// 護石スロット数変更
void AmuletSlotChange(MenuEntry *entry) {
  std::vector<std::string> listAmuletSlot{"0スロット", "1スロット", "2スロット",
                                          "3スロット"};

  Keyboard keyboard("スロット数を選んでください", listAmuletSlot);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(0x8386D8C, choice);
  }
}

// チャット無限
void ChatInfinite(MenuEntry *entry) { Process::Write8(0xDD4CA0, 0x0); }

// 装備コピー
void OtherPlayerEquipmentCopy(MenuEntry *entry) {
  std::vector<std::string> list1to4Player{"P1", "P2", "P3", "P4"};

  u32 equip[2][6];
  u32 online;
  Process::Read32(0x80913EC, online);
  Keyboard keyboard("装備をコピーしたいプレイヤーを選んで下さい",
                    list1to4Player);
  int choice = keyboard.Open();
  if (choice >= 0 && choice <= 3) {
    if (online == 0x100) {
      for (int i = 0; i < 6; i++) {
        Process::Read32(choice * 0x494 + i * 0x30 + 0x831C9E4, equip[0][i]);
        Process::Write32(choice * 0x494 + i * 0x30 + 0x8386C58, equip[0][i]);
        Process::Read32(choice * 0x494 + i * 0x4 + 0x831CB04, equip[1][i]);
        Process::Write32(choice * 0x494 + i * 0x4 + 0x8386D78, equip[1][i]);
      }
    } else {
      MessageBox("オフラインではコピーできません")();
    }
  }
}

// プレイヤー座標移動
void PlayerCoordinateModifier(MenuEntry *entry) {
  u32 offset;
  float x, z;
  Process::Read32(0x8195350, offset);
  Process::ReadFloat(offset + 0x40, x);
  Process::ReadFloat(offset + 0x48, z);

  if (Controller::IsKeysDown(A + DPadUp)) {
    Process::WriteFloat(offset + 0x48, z - 50);
  }
  if (Controller::IsKeysDown(A + DPadDown)) {
    Process::WriteFloat(offset + 0x48, z + 50);
  }
  if (Controller::IsKeysDown(A + DPadLeft)) {
    Process::WriteFloat(offset + 0x40, x - 50);
  }
  if (Controller::IsKeysDown(A + DPadRight)) {
    Process::WriteFloat(offset + 0x40, x + 50);
  }
}

// ムーンジャンプ
void PlayerMoonJump(MenuEntry *entry) {
  u32 offset;
  float y;
  Process::Read32(0x8195350, offset);
  Process::ReadFloat(offset + 0x44, y);

  if (Controller::IsKeysDown(R + B)) {
    Process::WriteFloat(offset + 0x44, y + 50);
  }
}

// 他プレイヤーストーカー
void Stalker(MenuEntry *entry) {
  u16 on;
  u32 player, p1, p2, p3, p4, p1x, p2x, p3x, p4x, p1y, p2y, p3y, p4y, p1z, p2z,
      p3z, p4z;
  static u8 playerRoomPosition;
  static bool isPlayer1Stalker = false;
  static bool isPlayer2Stalker = false;
  static bool isPlayer3Stalker = false;
  Process::Read32(0x8195350, player);
  Process::Read16(0x80913EC, on);
  Process::Read32(0x831B284, p1);
  Process::Read32(0x831B288, p2);
  Process::Read32(0x831B28C, p3);
  Process::Read32(0x831B290, p4);
  Process::Read32(p1 + 0x40, p1x);
  Process::Read32(p1 + 0x44, p1y);
  Process::Read32(p1 + 0x48, p1z);
  Process::Read32(p2 + 0x40, p2x);
  Process::Read32(p2 + 0x44, p2y);
  Process::Read32(p2 + 0x48, p2z);
  Process::Read32(p3 + 0x40, p3x);
  Process::Read32(p3 + 0x44, p3y);
  Process::Read32(p3 + 0x48, p3z);
  Process::Read32(p4 + 0x40, p4x);
  Process::Read32(p4 + 0x44, p4y);
  Process::Read32(p4 + 0x48, p4z);
  Process::Read8(0x831B1C8, playerRoomPosition);
  if (on == 0x100) {
    if (Controller::IsKeysPressed(R + DPadUp)) {
      isPlayer1Stalker = true;
      isPlayer2Stalker = false;
      isPlayer3Stalker = false;
      OSD::Notify("StalkerP1:" << Color::Green << "ON!");
    }
    if (Controller::IsKeysPressed(R + DPadRight)) {
      isPlayer1Stalker = false;
      isPlayer2Stalker = true;
      isPlayer3Stalker = false;
      OSD::Notify("StalkerP2:" << Color::Green << "ON!");
    }
    if (Controller::IsKeysPressed(R + DPadDown)) {
      isPlayer1Stalker = false;
      isPlayer2Stalker = false;
      isPlayer3Stalker = true;
      OSD::Notify("StalkerP3:" << Color::Green << "ON!");
    }
    if (Controller::IsKeysPressed(R + DPadLeft)) {
      isPlayer1Stalker = false;
      isPlayer2Stalker = false;
      isPlayer3Stalker = false;
      OSD::Notify("Stalker:" << Color::Red << "OFF!");
    }

    if (playerRoomPosition == 0x0) {
      if (isPlayer1Stalker == true && p2 != 0x0) {
        Process::Write32(player + 0x40, p2x);
        Process::Write32(player + 0x44, p2y);
        Process::Write32(player + 0x48, p2z);
      }
      if (isPlayer2Stalker == true && p3 != 0x0) {
        Process::Write32(player + 0x40, p3x);
        Process::Write32(player + 0x44, p3y);
        Process::Write32(player + 0x48, p3z);
      }
      if (isPlayer3Stalker == true && p4 != 0x0) {
        Process::Write32(player + 0x40, p4x);
        Process::Write32(player + 0x44, p4y);
        Process::Write32(player + 0x48, p4z);
      }
    }
    if (playerRoomPosition == 0x1) {
      if (isPlayer1Stalker == true && p1 != 0x0) {
        Process::Write32(player + 0x40, p1x);
        Process::Write32(player + 0x44, p1y);
        Process::Write32(player + 0x48, p1z);
      }
      if (isPlayer2Stalker == true && p3 != 0x0) {
        Process::Write32(player + 0x40, p3x);
        Process::Write32(player + 0x44, p3y);
        Process::Write32(player + 0x48, p3z);
      }
      if (isPlayer3Stalker == true && p4 != 0x0) {
        Process::Write32(player + 0x40, p4x);
        Process::Write32(player + 0x44, p4y);
        Process::Write32(player + 0x48, p4z);
      }
    }
    if (playerRoomPosition == 0x2) {
      if (isPlayer1Stalker == true && p1 != 0x0) {
        Process::Write32(player + 0x40, p1x);
        Process::Write32(player + 0x44, p1y);
        Process::Write32(player + 0x48, p1z);
      }
      if (isPlayer2Stalker == true && p2 != 0x0) {
        Process::Write32(player + 0x40, p2x);
        Process::Write32(player + 0x44, p2y);
        Process::Write32(player + 0x48, p2z);
      }
      if (isPlayer3Stalker == true && p4 != 0x0) {
        Process::Write32(player + 0x40, p4x);
        Process::Write32(player + 0x44, p4y);
        Process::Write32(player + 0x48, p4z);
      }
    }
    if (playerRoomPosition == 0x3) {
      if (isPlayer1Stalker == true && p1 != 0x0) {
        Process::Write32(player + 0x40, p1x);
        Process::Write32(player + 0x44, p1y);
        Process::Write32(player + 0x48, p1z);
      }
      if (isPlayer2Stalker == true && p2 != 0x0) {
        Process::Write32(player + 0x40, p2x);
        Process::Write32(player + 0x44, p2y);
        Process::Write32(player + 0x48, p2z);
      }
      if (isPlayer3Stalker == true && p3 != 0x0) {
        Process::Write32(player + 0x40, p3x);
        Process::Write32(player + 0x44, p3y);
        Process::Write32(player + 0x48, p3z);
      }
    }
  }
}

// モンスター座標移動
void MonsterCoordinateModifier(MenuEntry *entry) {
  float mon1x, mon1z, mon2x, mon2z;
  u32 offset1, offset2;
  u8 area1, area2;
  Process::Read32(0x8325244, offset1);
  Process::Read32(0x8325248, offset2);
  Process::ReadFloat(offset1 + 0xFF8, mon1x);
  Process::ReadFloat(offset1 + 0x1000, mon1z);
  Process::ReadFloat(offset2 + 0xFF8, mon2x);
  Process::ReadFloat(offset2 + 0x1000, mon2z);
  Process::Read8(offset1 + 0xD, area1);
  Process::Read8(offset2 + 0xD, area2);

  if (Controller::IsKeysDown(X)) {
    if (area1 == 0x4C) {
      if (Controller::IsKeysDown(DPadUp)) {
        Process::WriteFloat(offset1 + 0x1000, mon1z - 50);
      }
      if (Controller::IsKeysDown(DPadDown)) {
        Process::WriteFloat(offset1 + 0x1000, mon1z + 50);
      }
      if (Controller::IsKeysDown(DPadLeft)) {
        Process::WriteFloat(offset1 + 0xFF8, mon1x - 50);
      }
      if (Controller::IsKeysDown(DPadRight)) {
        Process::WriteFloat(offset1 + 0xFF8, mon1x + 50);
      }
    }
    if (area2 == 0x4C) {
      if (Controller::IsKeysDown(CPadUp)) {
        Process::WriteFloat(offset2 + 0x1000, mon2z - 50);
      }
      if (Controller::IsKeysDown(CPadDown)) {
        Process::WriteFloat(offset2 + 0x1000, mon2z + 50);
      }
      if (Controller::IsKeysDown(CPadLeft)) {
        Process::WriteFloat(offset2 + 0xFF8, mon2x - 50);
      }
      if (Controller::IsKeysDown(CPadRight)) {
        Process::WriteFloat(offset2 + 0xFF8, mon2x + 50);
      }
    }
  }
}

// モンスターストーカー
void MonsterStalker(MenuEntry *entry) {
  u32 player, mon1, mon2;
  u32 playerX, playerZ, mon1x, mon1z, mon2x, mon2z;
  u8 area1, area2;
  static bool ston1 = false;
  static bool ston2 = false;
  Process::Read32(0x8195350, player);
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Process::Read32(player + 0x40, playerX);
  Process::Read32(player + 0x48, playerZ);
  Process::Read32(mon1 + 0xFF8, mon1x);
  Process::Read32(mon1 + 0x1000, mon1z);
  Process::Read32(mon2 + 0xFF8, mon2x);
  Process::Read32(mon2 + 0x1000, mon2z);
  Process::Read8(mon1 + 0xD, area1);
  Process::Read8(mon2 + 0xD, area2);
  if (Controller::IsKeysPressed(X + DPadUp + R)) {
    ston1 = true;
    ston2 = false;
    OSD::Notify("Mon1Stalker:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(X + DPadUp + L)) {
    ston1 = false;
    ston2 = true;
    OSD::Notify("Mon2Stalker:" << Color::Green << "ON!");
  }
  if (Controller::IsKeysPressed(X + DPadDown + R)) {
    ston1 = false;
    ston2 = false;
    OSD::Notify("MonStalker:" << Color::Red << "OFF!");
  }
  if (ston1 == true) {
    if (area1 == 0x4C) {
      Process::Write32(player + 0x40, mon1x);
      Process::Write32(player + 0x48, mon1z);
    }
  }
  if (ston2 == true) {
    if (area2 == 0x4C) {
      Process::Write32(player + 0x40, mon2x);
      Process::Write32(player + 0x48, mon2z);
    }
  }
}

// 1番目のモンスターHP表示
void Monster1HpDisplay(MenuEntry *entry) {
  u32 offset;
  static u16 mon1HpMax, mon1Hp;
  static int addressOn = 0;
  addressOn = true;
  Process::Read32(0x8325244, offset);
  Process::Read16(offset + 0x1318, mon1Hp);
  Process::Read16(offset + 0x131C, mon1HpMax);

  if (offset != 0) {
    addressOn = true;
    OSD::Run([](const Screen &screen) {
      if (!screen.IsTop) {
        return (false);
      }
      if (addressOn == true) {
        if (mon1Hp == 0) {  // 0%
          screen.Draw(Utils::Format("Mon1HP %u", mon1Hp), 10, 100, Color::Gray);
          addressOn = false;
        } else if (mon1Hp * 5 < mon1HpMax) {  // 20%
          screen.Draw(Utils::Format("Mon1HP %u", mon1Hp), 10, 100, Color::Red);
          addressOn = false;
        } else if (mon1Hp * 2 < mon1HpMax) {  // 50%
          screen.Draw(Utils::Format("Mon1HP %u", mon1Hp), 10, 100,
                      Color::Orange);
          addressOn = false;
        } else {
          screen.Draw(Utils::Format("Mon1HP %u", mon1Hp), 10, 100,
                      Color::Green);
          addressOn = false;
        }
      }
      return (true);
    });
  } else
    addressOn = false;
}

// 2番目のモンスターHP表示
void Monster2HpDisplay(MenuEntry *entry) {
  u32 offset;
  static u16 mon2HpMax, mon2Hp;
  static int addressOn = 0;
  Process::Read32(0x8325248, offset);
  Process::Read16(offset + 0x1318, mon2Hp);
  Process::Read16(offset + 0x131C, mon2HpMax);
  if (offset != 0) {
    addressOn = true;
    OSD::Run([](const Screen &screen) {
      if (!screen.IsTop) {
        return (false);
      }
      if (addressOn == true) {
        if (mon2Hp == 0) {  // 0
          screen.Draw(Utils::Format("Mon2HP %u", mon2Hp), 10, 110, Color::Gray);
          addressOn = false;
        } else if (mon2Hp * 5 < mon2HpMax) {  // 20%
          screen.Draw(Utils::Format("Mon2HP %u", mon2Hp), 10, 110, Color::Red);
          addressOn = false;
        } else if (mon2Hp * 2 < mon2HpMax) {  // 50%
          screen.Draw(Utils::Format("Mon2HP %u", mon2Hp), 10, 110,
                      Color::Orange);
          addressOn = false;
        } else {
          screen.Draw(Utils::Format("Mon2HP %u", mon2Hp), 10, 110,
                      Color::Green);
          addressOn = false;
        }
      }
      return (true);
    });
  } else
    addressOn = false;
}

// プレイヤーの現在座標表示
void DisplayPlayerCoordinate(MenuEntry *entry) {
  u32 offset;
  static float x, y, z;
  static int addressOn = 0;
  addressOn = true;
  Process::Read32(0x8195350, offset);
  Process::ReadFloat(offset + 0x40, x);
  Process::ReadFloat(offset + 0x44, y);
  Process::ReadFloat(offset + 0x48, z);
  OSD::Run([](const Screen &screen) {
    if (!screen.IsTop) {
      return (false);
    }
    if (addressOn == true) {
      screen.Draw(Utils::Format("Player X=%.f Y=%.f Z=%.f", x, y, z), 10, 50,
                  Color::Yellow);
      addressOn = false;
    }
    return (true);
  });
}

// リージョン変更
void RegionChange(MenuEntry *entry) {
  std::vector<std::string> listRegion{"日本", "ヨーロッパ"};

  Keyboard keyboard("リージョンを選択してください。", listRegion);
  int result = keyboard.Open();
  if (result == 0) {
    Process::Write32(0x389BC4, 0xE3A01000);
  }
  if (result == 1) {
    Process::Write32(0x389BC4, 0xE3A01001);
  }
}

// リピートムーブ
void Repeatmove(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8195350, offset);
  if (Controller::IsKeysDown(B + Y)) {
    Process::Write32(offset + 0x5, 0);
  }
}

// 特殊チケット変更
void SpecialPermitQuestTicketChange(MenuEntry *entry) {
  std::vector<std::string> listSpecialTicket{
      "紅兜アオアシラ", "大雪主ウルクスス", "矛砕ダイミョウザザミ",
      "紫毒姫リオレイア", "岩穿テツカブラ", "白疾風ナルガクルガ",
      "宝纏ウラガンキン", "隻眼イャンガルルガ", "黒炎王リオレウス",
      "金雷公ジンオウガ", "荒鉤爪ティガレックス", "燼滅刃ディノバルド"};

  u8 ticket;
  Keyboard keyboard("変更したいチケットを選んでください。", listSpecialTicket);
  int result = keyboard.Open();
  if (result == 0) {
    Keyboard keyboard("何枚に変えますか?");
    keyboard.IsHexadecimal(false);
    keyboard.Open(ticket);
    for (int i = 0; i < 12; i++) {
      Process::Write8(result * 0x1 + 0x83B3835, ticket);
    }
  }
}

static u32 questClearFail;
// クエストクリア失敗変更
void QuestClearOption(MenuEntry *entry) {
  std::vector<std::string> listQuestClear{"クエストクリア", "クエスト失敗"};

  Keyboard keyboard("クエストクリアか失敗かを選んでください。", listQuestClear);
  int choice = keyboard.Open();
  if (choice == 0) {
    questClearFail = 0x29;
  }
  if (choice == 1) {
    questClearFail = 0xC9;
  }
}

// クエストクリア失敗固定
void QuestClear(MenuEntry *entry) {
  Process::Write32(0x8363F94, questClearFail);
  Process::Write32(0x8363FA0, questClearFail);
}

// クエスト後即リザルト
void QuestResultSkip(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x83ACA40, offset);
  Process::Write32(offset + 0x104, 0);
}

// 報酬画面スキップ
void QuestWaitSkip(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x819DF68, offset);
  Process::Write32(offset + 0xAC, 0);
}

// たんほれアイテム
void TanhoreItemSet(MenuEntry *entry) {
  Process::Write16(0x8372392, 0x0527);  // 燃石炭
  Process::Write8(0x8372394, 0x63);
  Process::Write16(0x8372396, 0x0455);  // ネコタクチケット
  Process::Write8(0x8372398, 0x63);
  Process::Write16(0x837239A, 0x004C);  // モドリ玉
  Process::Write8(0x837239C, 0x63);
}

// 爆弾無限設置
void InfiniteBombPut(MenuEntry *entry) { Process::Write32(0x83AC5F0, 0x3); }

// 視野角変更設定
static float fov = 50.f;
void ViewingAngleOption(MenuEntry *entry) {
  std::vector<std::string> listViewingAngle{"デフォルト", "視野角変更"};

  Keyboard keyboard("どちらにしますか？", listViewingAngle);
  int result = keyboard.Open();
  if (result == 0) {
    fov = 50.f;
  }
  if (result == 1) {
    Keyboard keyboard(
        Utils::Format("視野角を指定してください。\n現在の視野角[%f]", fov));
    keyboard.Open(fov);
  }
}

// 視野角変更
void ViewingAngleChange(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x81943DC, offset);
  Process::WriteFloat(offset + 0x740, fov);
}

// 村貢献度
void VillageContributionPointChange(MenuEntry *entry) {
  u32 contributionPoint;
  std::vector<std::string> listVillage{"ベルナ村", "ココット村", "ポッケ村",
                                       "ユクモ村"};

  Keyboard keyboard("貢献度を変更したい村を選んでください。", listVillage);
  int result = keyboard.Open();
  if (result == 0) {
    Keyboard keyboard("貢献度を入力してください。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(contributionPoint) != -1) {
      Process::Write32(0x83B3824, contributionPoint);
    }
  }
  if (result == 1) {
    Keyboard keyboard("貢献度を入力してください。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(contributionPoint) != -1) {
      Process::Write32(0x83B3828, contributionPoint);
    }
  }
  if (result == 2) {
    Keyboard keyboard("貢献度を入力してください。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(contributionPoint) != -1) {
      Process::Write32(0x83B382C, contributionPoint);
    }
  }
  if (result == 3) {
    Keyboard keyboard("貢献度を入力してください。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(contributionPoint) != -1) {
      Process::Write32(0x83B3830, contributionPoint);
    }
  }
}

// ルームサービス変更
void RoomServiceChange(MenuEntry *entry) {
  std::vector<std::string> listRoomService{
      "ルームサービス", "キャラバンの看板娘", "モガの村の看板娘",
      "タンジアの港の看板娘", "ぽかぽか島の管理人"};

  Keyboard keyboard("どのルームサービスに変更しますか？", listRoomService);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(0x83B36D0, choice);
  }
}

// ギルドカード変更
void GuildCardChange(MenuEntry *entry) {
  std::vector<std::string> listGuildCardChangeGroup{
      "称号", "クリア回数", "すれ違い回数",
      "友好度", "背景", "ポーズ",
      "武器使用回数", "プレイ時間", "モンスター狩猟記録"};

  std::vector<std::string> listGuildCardChangeTitle{"称号1", "称号2", "称号3"};

  std::vector<std::string> listGuildCardChangeClearValue{
      "村", "集会所下位", "集会所上位", "特殊許可クエスト", "闘技大会"};

  std::vector<std::string> listGuildCardChangeWeaponUseGroup{
      "村", "集会所", "闘技大会", "全てカンスト"};

  std::vector<std::string> listGuildCardChangeWeaponUseType{
      "大剣", "片手剣",
      "ハンマー", "ランス",
      "ヘビィボウガン", "ライトボウガン",
      "太刀", "スラッシュアックス",
      "ガンランス", "弓",
      "双剣", "狩猟笛",
      "操虫棍", "チャージアックス",
      "ニャンター"};

  std::vector<std::string> listGuildCardChangeMonsterHuntingGroup{
      "狩猟数", "捕獲数", "どちらもカンスト"};

  std::vector<std::string> listGuildCardChangeMonsterHuntingBigSmall{
      "大型モンスター", "小型モンスター"};

  std::vector<std::string> listGuildCardChangeMonsterHuntingBig{
      "リオレイア",
      "リオレイア希少種",
      "紫毒姫リオレイア",
      "リオレウス",
      "リオレウス希少種",
      "黒炎王リオレウス",
      "フルフル",
      "イャンクック"
      "ゲリョス",
      "ガノトトス",
      "キリン",
      "ドスランポス",
      "ドスゲネポス",
      "ドスイーオス",
      "ドスガレオス",
      "イャンガルルガ",
      "隻眼イャンガルルガ",
      "ダイミョウザザミ",
      "矛砕ダイミョウザザミ",
      "ショウグンギザミ",
      "ドドブランゴ",
      "ラージャン",
      "激昂したラージャン",
      "クシャルダオラ",
      "オオナズチ",
      "テオ・テスカトル",
      "ドスファンゴ",
      "ティガレックス",
      "荒鉤爪ティガレックス",
      "アカムトルム",
      "ヴォルガノス",
      "ナルガクルガ",
      "白疾風ナルガクルガ",
      "ウカムルバス",
      "イビルジョー",
      "怒り喰らうイビルジョー",
      "ウラガンキン",
      "宝纏ウラガンキン",
      "ラギアクルス",
      "ロアルドロス",
      "アグナコトル",
      "アルバトリオン",
      "ドボルベルク",
      "ハプルボッカ",
      "ジンオウガ",
      "金雷公ジンオウガ"
      "アマツマガツチ",
      "アオアシラ",
      "紅兜アオアシラ",
      "ウルクスス",
      "大雪主ウルクスス",
      "ラングロトラ",
      "ブラキディオス",
      "ケチャワチャ",
      "テツカブラ",
      "岩穿テツカブラ",
      "ザボアザギル",
      "ガララアジャラ",
      "ゲネル・セルタス",
      "ゴア・マガラ",
      "シャガルマガラ",
      "アルセルタス",
      "セルレギオス",
      "ホロロホルル",
      "ディノバルド",
      "燼滅刃ディノバルド",
      "ライゼクス",
      "タマミツネ",
      "ガムート",
      "オストガロア",
      "ドスマッカォ"};

  std::vector<std::string> listGuildCardChangeMonsterHuntingSmall{
      "アプトノス", "アプケロス", "ケルビ", "モス", "カンタロス",
      "ランゴスタ", "アイルー", "メラルー", "ランポス", "ゲネポス",
      "イーオス", "ガレオス", "ブルファンゴ", "ポポ", "ギアノス",
      "ガウシカ", "ガブラス", "ヤオザミ", "ガミザミ", "ブランゴ",
      "リノプロス", "ブナハブラ", "オルタロス", "ジャギィ", "ジャギィノス",
      "ルドロス", "ウロコトル", "ズワロポス", "ガーグァ", "スクアギル",
      "クンチュウ", "マッカォ", "リモセトス", "ムーファ"};

  u16 title1, title2, title3, value;
  float friendShipPoint;
  Keyboard keyboard("グループを選択してください。", listGuildCardChangeGroup);
  int result = keyboard.Open();
  if (result == 0) {
    Keyboard keyboard("下画面の説明文に変更する称号を選んでください。",
                      listGuildCardChangeTitle);
    int title = keyboard.Open();
    if (title == 0) {
      Process::Read16(0x8436978, title1);
      Process::Write16(0x8436978, title + 0x3D4);
    }
    if (title == 1) {
      Process::Write16(0x843697A, 0x65);
    }
    if (title == 2) {
      Process::Read16(0x843697C, title3);
      Process::Write16(0x843697C, title3 + 0x3D4);
    }
  }
  if (result == 1) {
    Keyboard keyboard("変更するクリア回数を選んでください。",
                      listGuildCardChangeClearValue);
    int clear = keyboard.Open();
    Keyboard key("クリア回数を入力してください。");
    key.IsHexadecimal(false);
    key.Open(value);
    if (clear >= 0) {
      for (int i = 0; i < 5; i++) {
        if (clear == i) {
          Process::Write16(i * 0x2 + 0x843697E, value);
        }
      }
    }
  }
  if (result == 2) {
    Keyboard keyboard("すれ違い回数を入力してください。");
    keyboard.IsHexadecimal(false);
    int sure = keyboard.Open(value);
    if (sure >= 0) {
      Process::Write16(0x843698C, value);
    }
  }
  if (result == 3) {
    Keyboard keyboard("友好度を入力してください。");
    keyboard.IsHexadecimal(false);
    int friendShip = keyboard.Open(friendShipPoint);
    if (friendShip >= 0) {
      Process::WriteFloat(0x8436988, friendShipPoint);
    }
  }
  if (result == 4) {
    Keyboard keyboard("背景を透明にしますか？", listToggle);
    int choice = keyboard.Open();
    if (choice == 0) {
      Process::Write8(0x84369CA, 0x5E);
    }
  }
  if (result == 5) {
    Keyboard keyboard("ポーズをTポーズにしますか？", listToggle);
    int choice = keyboard.Open();
    if (choice == 0) {
      Process::Write8(0x84369CB, 0x16);
    }
  }
  if (result == 6) {
    Keyboard keyboard("グループを選んでください。",
                      listGuildCardChangeWeaponUseGroup);
    int gurupu = keyboard.Open();
    if (gurupu >= 0 && gurupu <= 2) {
      Keyboard keyboard("武器種を選んでください。",
                        listGuildCardChangeWeaponUseType);
      int choice = keyboard.Open();
      if (choice >= 0) {
        Keyboard keyboard("武器使用回数を入力してください。");
        keyboard.IsHexadecimal(false);
        keyboard.Open(value);
        for (int i = 0; i < 14; i++) {
          if (choice == i) {
            Process::Write16(i * 0x2 + gurupu * 0x1E + 0x84369D4, value);
          }
        }
      }
    }
    if (gurupu == 3) {
      Keyboard keyboard("全ての武器使用回数を9999にしますか？", listToggle);
      int choice = keyboard.Open();
      if (choice == 0) {
        for (int i = 0; i < 45; i++) {
          Process::Write16(i * 0x2 + 0x84369D4, 0x270F);
        }
      }
    }
  }
  if (result == 7) {
    u32 timeSecond, timeMinute, timeHour, time;
    Keyboard secondKeyboard("プレイ時間(秒)を入力してください。");
    secondKeyboard.IsHexadecimal(false);
    secondKeyboard.Open(timeSecond);
    Keyboard minuteKeyboard("プレイ時間(分)を入力してください。");
    minuteKeyboard.IsHexadecimal(false);
    minuteKeyboard.Open(timeMinute);
    Keyboard hourKeyboard("プレイ時間(時)を入力してください。");
    hourKeyboard.IsHexadecimal(false);
    hourKeyboard.Open(timeHour);
    timeMinute = timeMinute * 60;
    timeHour = timeHour * 3600;
    time = timeSecond + timeMinute + timeHour;
    Process::Write32(0x831B1CC, time);
  }
  if (result == 8) {
    Keyboard keyboard("グループを選んでください。",
                      listGuildCardChangeMonsterHuntingGroup);
    int huntingGroup = keyboard.Open();
    if (huntingGroup == 0) {
      Keyboard keyboard("ページを選んでください。\n(ギルドカードの並びです)",
                        listGuildCardChangeMonsterHuntingBigSmall);
      int huntPage = keyboard.Open();
      if (huntPage == 0) {
        Keyboard monsterChoice("モンスターを選んでください。",
                               listGuildCardChangeMonsterHuntingBig);
        int bigMonster = monsterChoice.Open();
        Keyboard keyboard("討伐数を入力してください。");
        keyboard.IsHexadecimal(false);
        keyboard.Open(value);
        if (value >= 0) {
          for (int i = 0; i < 71; i++) {
            if (bigMonster == i) {
              Process::Write16(i * 2 + 0x83B3D6A, value);
            }
          }
        }
      }
      if (huntPage == 1) {
        Keyboard monsterChoice("小型モンスターを選んでください。",
                               listGuildCardChangeMonsterHuntingSmall);
        monsterChoice.IsHexadecimal(false);
        int smallMonster = monsterChoice.Open();
        Keyboard keyboard("討伐数を入力してください。");
        keyboard.IsHexadecimal(false);
        keyboard.Open(value);
        if (value >= 0) {
          for (int i = 0; i < 34; i++) {
            if (smallMonster == i) {
              Process::Write16(i * 2 + 0x83B3E06, value);
            }
          }
        }
      }
      if (huntingGroup == 1) {
        Keyboard monsterChoice("モンスターを選んでください。",
                               listGuildCardChangeMonsterHuntingBig);
        monsterChoice.IsHexadecimal(false);
        int bigMonster = monsterChoice.Open();
        Keyboard keyboard("捕獲数を入力してください。");
        keyboard.IsHexadecimal(false);
        keyboard.Open(value);
        if (value >= 0) {
          for (int i = 0; i < 71; i++) {
            if (bigMonster == i) {
              Process::Write16(0x83B3E4C, value);
            }
          }
        }
      }
      if (huntingGroup == 2) {
        Keyboard keyboard("全ての狩猟数と捕獲数を9999にしますか？", listToggle);
        int choice = keyboard.Open();
        if (choice == 0) {
          for (int i = 0; i < 67; i++) {
            Process::Write16(i * 2 + 0x83B3D6C, 9999);
          }
          for (int i = 0; i < 47; i++) {
            Process::Write16(i * 2 + 0x83B3E4C, 9999);
          }
        }
      }
    }
  }
}

// セーブ画面選択肢固定設定
static u8 saveFix;
void SaveScreenOption(MenuEntry *entry) {
  Keyboard keyboard("セーブ画面をどちらで固定しますか？", listToggle);
  int choice = keyboard.Open();
  if (choice != -1) {
    saveFix = choice;
  }
}

// セーブ画面選択肢固定
void SaveScreenFix(MenuEntry *entry) {
  if (Controller::IsKeysDown(R)) {
    Process::Write8(0x306E29A0, saveFix);
  }
}

// アイテムボックス編集
void ItemBoxEdit(MenuEntry *entry) {
  u16 data16;
  std::vector<std::string> listItemBoxEdit{"アイテムを入れる[1400種]",
                                           "アイテムを入れる[548種]",
                                           "全アイテム99個", "全アイテム消去"};

  Keyboard keyboard("アイテムボックスをどう編集しますか？", listItemBoxEdit);
  int choice = keyboard.Open();
  if (choice == 0) {
    Process::Write16(0x8372562, 0x1);
    for (int i = 0; i < 1400; i++) {
      Process::Read16(i * 4 + 0x8372562, data16);
      Process::Write16(i * 4 + 0x8372566, data16 + 1);
    }
  }
  if (choice == 1) {
    Process::Write16(0x8372562, 0x578);
    for (int i = 0; i < 548; i++) {
      Process::Read16(i * 4 + 0x8372562, data16);
      Process::Write16(i * 4 + 0x8372566, data16 + 1);
    }
    for (int i = 0; i < 851; i++) {
      Process::Write32(i * 4 + 0x8372DF6, 0x0);
    }
  }
  if (choice == 2) {
    for (int i = 0; i < 1400; i++) {
      Process::Write16(i * 4 + 0x8372564, 0x63);
    }
  }
  if (choice == 3) {
    if (MessageBox("確認です", "全て削除してもいいですか？",
                   DialogType::DialogYesNo)()) {
      for (int i = 0; i < 1400; i++) {
        Process::Write32(i * 4 + 0x8372562, 0x0);
      }
    }
  }
}

// アイテムポーチ消去
void PorchAllClear(MenuEntry *entry) {
  if (MessageBox("確認です", "全て削除してもいいですか？",
                 DialogType::DialogYesNo)()) {
    for (int i = 0; i < 32; i++) {
      Process::Write32(i * 4 + 0x8372392, 0x0);
    }
  }
}

// トリプルアップ
void InsectGlaiveAlwaysTripleUp(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::WriteFloat(offset + 0x1FF8, 3600);
  Process::WriteFloat(offset + 0x1FFC, 3600);
  Process::WriteFloat(offset + 0x2000, 3600);
}

// 猟虫スタミナ無限
void InsectGlaiveInsectStaminaInfinite(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write16(offset + 0x2010, 0x82);
}

// 溜め段階固定設定
static float tame = 0;
void ChageStageOption(MenuEntry *entry) {
  std::vector<std::string> listStageSelect{"0段階目", "1段階目", "2段階目",
                                           "3段階目", "4段階目"};

  static int stage = 0;
  Keyboard keyboard(
      Utils::Format("溜め段階を選んでください。\n現在[%u段階目]", stage),
      listStageSelect);
  int choice = keyboard.Open();
  if (choice == 0) {
    tame = 0;
    stage = 0;
  }
  if (choice == 1) {
    tame = 40;
    stage = 1;
  }
  if (choice == 2) {
    tame = 80;
    stage = 2;
  }
  if (choice == 3) {
    tame = 120;
    stage = 3;
  }
  if (choice == 4) {
    tame = 144;
    stage = 4;
  }
}

// 溜め段階固定
void ChargeStageFix(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::WriteFloat(offset + 0x1914, tame);
}

// 武器ゲージ
void WeaponGageFix(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write16(offset + 0x1598, 0x64);
}

// チャアクビン
void ChargeAxeBinFix(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write8(offset + 0x1922, 0x5);
}

// 笛全効果付与
void HuntingHornAllEffectGrant(MenuEntry *entry) {
  u32 questFrame1, offset;
  Process::Read32(0x8363ED4, questFrame1);
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  if (questFrame1 != 0) {
    for (int i = 0; i < 32; i++) {
      Process::WriteFloat(offset + i * 4 + 0x17D0, 10);
    }
  }
}

// 弾数
void BowgunAmmoInfinite(MenuEntry *entry) {
  u8 ammo;
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Read8(offset + 0x1924, ammo);
  Process::Write8(offset + 0x1922, ammo);
}

// しゃがみ
void BowgunCrouchingShot(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write8(offset + 0x1FF6, 0x7F);
}

// 1番目のモンスターサイズ表示
void Monster1SizeMagnificationDisplay(MenuEntry *entry) {
  u32 offset;
  static float mon1size;
  static int addressOn = 0;
  addressOn = true;
  Process::Read32(0x8325244, offset);
  Process::ReadFloat(offset + 0x1168, mon1size);

  if (offset != 0) {
    addressOn = true;
    OSD::Run([](const Screen &screen) {
      if (!screen.IsTop) {
        return (false);
      }
      if (addressOn == true) {
        screen.Draw(Utils::Format("Mon1SZ %.2f", mon1size), 10, 120,
                    Color::Yellow);
        addressOn = false;
      }
      return (true);
    });
  } else
    addressOn = false;
}

// 2番目のモンスターサイズ表示
void Monster2SizeMagnificationDisplay(MenuEntry *entry) {
  u32 offset;
  static float mon2size;
  static int addressOn = 0;
  addressOn = true;
  Process::Read32(0x8325248, offset);
  Process::ReadFloat(offset + 0x1168, mon2size);

  if (offset != 0) {
    addressOn = true;
    OSD::Run([](const Screen &screen) {
      if (!screen.IsTop) {
        return (false);
      }
      if (addressOn == true) {
        screen.Draw(Utils::Format("Mon2SZ %.2f", mon2size), 10, 130,
                    Color::Yellow);
        addressOn = false;
      }
      return (true);
    });
  } else
    addressOn = false;
}

// モンスターリピート設定
static int mon1act, mon2act;
void MonsterActionRepeatOption(MenuEntry *entry) {
  Keyboard keyboard("挙動を選んでください。", {"固まる", "なめらか"});
  int choice = keyboard.Open();
  if (choice == 0) {
    mon1act = true;
    mon2act = true;
  }
  if (choice == 1) {
    mon1act = false;
    mon2act = false;
  }
}

// モンスターリピート
void MonsterActionRepeat(MenuEntry *entry) {
  u32 mon1, mon2;
  u8 area1, area2;
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Process::Read8(mon1 + 0xD, area1);
  Process::Read8(mon2 + 0xD, area2);
  if (Controller::IsKeysDown(X + DPadRight)) {
    if (Controller::IsKeysDown(R)) {
      if (area1 == 0x4C) {
        if (mon1act == true) {
          Process::Write16(mon1 + 0x1158, 0x0);
        }
        if (mon1act == false) {
          Process::Write8(mon1 + 0x1159, 0x0);
        }
      }
    }
    if (Controller::IsKeysDown(L)) {
      if (area2 == 0x4C) {
        if (mon2act == true) {
          Process::Write16(mon1 + 0x1158, 0x0);
        }
        if (mon2act == false) {
          Process::Write8(mon1 + 0x1159, 0x0);
        }
      }
    }
  }
}

// 1番目と2番目のモンスター停止
void Monster1And2Stop(MenuEntry *entry) {
  u32 mon1, mon2;
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Process::Write16(mon1 + 0x1158, 0x0);
  Process::Write16(mon2 + 0x1158, 0x0);
}

// 1番目のモンスター速度変更設定
static float mon1sp = 1;
static float mon2sp = 1;
void Monster1SpeedAttributeOption(MenuEntry *entry) {
  Keyboard keyboard(
      Utils::Format("速度倍率を入力してください。\n現在[%.2f]", mon1sp));
  keyboard.IsHexadecimal(false);
  keyboard.Open(mon1sp);
}

// 2番目のモンスター速度変更設定
void Monster2SpeedAttributeOption(MenuEntry *entry) {
  Keyboard keyboard(
      Utils::Format("速度倍率を入力してください。\n現在[%.2f]", mon2sp));
  keyboard.IsHexadecimal(false);
  keyboard.Open(mon2sp);
}

// 1番目のモンスター速度変更
void Monster1SpeedAttributeChange(MenuEntry *entry) {
  u32 mon1;
  Process::Read32(0x8325244, mon1);
  Process::WriteFloat(mon1 + 0x2A4, mon1sp);
}

// 2番目のモンスター速度変更
void Monster2SpeedAttributeChange(MenuEntry *entry) {
  u32 mon2;
  Process::Read32(0x8325248, mon2);
  Process::WriteFloat(mon2 + 0x2A4, mon2sp);
}

// 1番目と2番目のモンスター透明
void Monster1And2AlwaysInvisible(MenuEntry *entry) {
  u32 mon1, mon2;
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Keyboard keyboard("透明にしますか？", listToggle);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(mon1 + 0x115C, choice);
    Process::Write8(mon2 + 0x115C, choice);
  }
}

// 1番目と2番目のモンスター毒
void Monster1And2AlwaysPoison(MenuEntry *entry) {
  u32 mon1, mon2;
  u16 poison1Max, poison2Max;
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Process::Read16(mon1 + 0x6820, poison1Max);
  Process::Read16(mon2 + 0x6820, poison2Max);
  Process::Write16(mon1 + 0x6814, poison1Max);
  Process::Write16(mon2 + 0x6814, poison2Max);
}

// 1番目と2番目のモンスター麻痺
void Monster1And2AlwaysParalysis(MenuEntry *entry) {
  u32 mon1, mon2;
  u16 paralysis1Max, paralysis2Max;
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Process::Read16(mon1 + 0x682C, paralysis1Max);
  Process::Read16(mon2 + 0x682C, paralysis2Max);
  Process::Write16(mon1 + 0x682E, paralysis1Max);
  Process::Write16(mon2 + 0x682E, paralysis2Max);
}

// 1番目と2番目のモンスター睡眠
void Monster1And2AlwaysSleep(MenuEntry *entry) {
  u32 mon1, mon2;
  u16 sleep1Max, sleep2Max;
  Process::Read32(0x8325244, mon1);
  Process::Read32(0x8325248, mon2);
  Process::Read16(mon1 + 0x6816, sleep1Max);
  Process::Read16(mon2 + 0x6816, sleep2Max);
  Process::Write16(mon1 + 0x6818, sleep1Max);
  Process::Write16(mon2 + 0x6816, sleep2Max);
}

// 1番目のモンスターサイズ変更設定
static float monster1Size = 1;
static float monster2Size = 1;
void Monster1SizeOption(MenuEntry *entry) {
  u32 mon1;
  Process::Read32(0x8325244, mon1);
  Process::ReadFloat(mon1 + 0x1168, monster1Size);
  Keyboard keyboard(Utils::Format("サイズ倍率を入力してください。\n現在[%.2f]",
                                  monster1Size));
  keyboard.IsHexadecimal(false);
  keyboard.Open(monster1Size);
}

// 1番目のモンスターサイズ変更
void Monster1SizeChange(MenuEntry *entry) {
  u32 mon1;
  Process::Read32(0x8325244, mon1);
  Process::WriteFloat(mon1 + 0x1168, monster1Size);
}

// 2番目のモンスターサイズ変更設定
void Monster2SizeOption(MenuEntry *entry) {
  u32 mon2;
  Process::Read32(0x8325248, mon2);
  Process::WriteFloat(mon2 + 0x1168, monster2Size);
  Keyboard keyboard(Utils::Format("サイズ倍率を入力してください。\n現在[%.2f]",
                                  monster2Size));
  keyboard.IsHexadecimal(false);
  keyboard.Open(monster2Size);
}

// 1番目のモンスターサイズ変更
void Monster2SizeChange(MenuEntry *entry) {
  u32 mon2;
  Process::Read32(0x8325248, mon2);
  Process::WriteFloat(mon2 + 0x1168, monster2Size);
}

// クエスト最大ダウン回数設定
static u8 quedownmax, quedownnow;
void QuestDownMaxOption(MenuEntry *entry) {
  Process::Read8(0x8365440, quedownmax);
  Keyboard keyboard(Utils::Format(
      "最大ダウン回数を入力してください。\n現在[%u]", quedownmax));
  keyboard.IsHexadecimal(false);
  keyboard.Open(quedownmax);
}

// クエスト最大ダウン回数
void QuestDownMaxChange(MenuEntry *entry) {
  Process::Write8(0x8365440, quedownmax);
}

// クエスト現在ダウン回数設定
void QuestDownNowOption(MenuEntry *entry) {
  Process::Read8(0x8365440, quedownnow);
  Keyboard keyboard(Utils::Format(
      "現在のダウン回数を入力してください。\n現在[%u]", quedownnow));
  keyboard.IsHexadecimal(false);
  keyboard.Open(quedownnow);
}

// クエスト現在ダウン回数
void QuestDownNowChange(MenuEntry *entry) {
  Process::Write8(0x8365440, quedownnow);
}

// クエスト残り時間表示
void QuestTimeDisplay(MenuEntry *entry) {
  static u32 questFrame1, questFrame2, questSecondAll, questSecond1,
      questSecond2;
  static u32 questMinuteAll, questMinute1, questMinute2, questHour1, questHour2;
  static int addressOn = 0;
  addressOn = true;
  Process::Read32(0x8363ED4, questFrame1);
  questFrame2 = questFrame1 % 60;

  questHour2 = questFrame1 / 216000;
  questMinuteAll = questHour2 * 60;
  questMinute2 = questFrame1 / 3600 - questMinuteAll;
  questSecondAll = questMinute2 * 60;
  questSecond2 = questFrame1 / 60 - questHour2 * 3600 - questSecondAll;

  if (questFrame1 != 0) {
    addressOn = true;
    OSD::Run([](const Screen &screen) {
      if (!screen.IsTop) {
        return (false);
      }
      if (addressOn == true) {
        if (questFrame1 <= 3600) {
          screen.Draw(Utils::Format("QT %d:%02d:%02d:%02d", questHour2,
                                    questMinute2, questSecond2, questFrame2),
                      10, 180, Color::Red);
          addressOn = false;
        } else {
          screen.Draw(Utils::Format("QT %d:%02d:%02d:%02d", questHour2,
                                    questMinute2, questSecond2, questFrame2),
                      10, 180, Color::Yellow);
          addressOn = false;
        }
      }
      return (true);
    });
  } else
    addressOn = false;
}

// ハンターランクポイント変更
void HunterRankPointChange(MenuEntry *entry) {
  u32 hrp;
  Process::Read32(0x83B3814, hrp);
  Keyboard keyboard(Utils::Format("HRPを入力してください。\n現在[%d]", hrp));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(hrp) != -1) {
    Process::Write32(0x83B3814, hrp);
  }
}

// 全クエストクリア未クリア
void AllQuestClearChange(MenuEntry *entry) {
  std::vector<std::string> listAllQuestClearSelect{"クエスト全クリア",
                                                   "クエスト全未クリア"};

  Keyboard keyboard("クエスト全クリアか、未クリアか選んでください。",
                    listAllQuestClearSelect);
  int choice = keyboard.Open();
  if (choice == 0) {
    for (int i = 0; i < 0x1C; i++) {
      Process::Write32(i * 0x4 + 0x83B3A6C, 0xFFFFFFFF);
    }
  }
  if (choice == 1) {
    for (int i = 0; i < 0x1C; i++) {
      Process::Write32(i * 0x4 + 0x83B3A6C, 0x0);
    }
  }
}

// フェニープーギーの名前変更
void FenyAndPugyNameChange(MenuEntry *entry) {
  std::string name;
  std::vector<std::string> listVillage{"ベルナ村", "ココット村", "ポッケ村",
                                       "ユクモ村"};

  Process::ReadString(0x83AE380, name, 0x1E, StringFormat::Utf8);
  Keyboard keyboard("グループを選んでください。", listVillage);
  int choice = keyboard.Open();
  if (choice == 0) {
    Process::WriteString(0x83B3648, name, StringFormat::Utf8);
  }
  if (choice == 1) {
    Process::WriteString(0x83B3668, name, StringFormat::Utf8);
  }
  if (choice == 2) {
    Process::WriteString(0x83B3688, name, StringFormat::Utf8);
  }
  if (choice == 3) {
    Process::WriteString(0x83B36A8, name, StringFormat::Utf8);
  }
}

// フェニープーギーの服変更
void FenyAndPugyClothes(MenuEntry *entry) {
  std::vector<std::string> listFenyClothes{"ルンルンベル", "愛しのマドモワゼル",
                                           "召しませ姫林檎", "常夏リゾート"};

  std::vector<std::string> listPugyClothes{
      "思い出ストライプ", "夢追いアミーゴ", "はだかの王様",
      "魅惑のピンク", "緑と黒の衝撃", "眠りを誘う白",
      "ドリームスター", "天使のレオタード", "カエルのマーチ",
      "ひよっこアフロ", "ブラックハニー", "純真クレナイ",
      "おシノビ裝束", "マフモフウォーマー", "ブンブンビー",
      "ファンキーアフロ", "いやされムーチョ", "さすらい道中",
      "チューボー見習い", "あやかし装束", "あまくちピンク",
      "なき虫ベイビー", "なついろ恋浴衣", "モスのきもち",
      "ルドロスウォーマー", "ウーパールンバ", "イビルのきもち",
      "ドスのきもち", "ハートの女王様", "パンプキンナイト",
      "キラキラ★ナイト"};

  std::vector<std::string> listVillage{"ベルナ村", "ココット村", "ポッケ村",
                                       "ユクモ村"};

  Keyboard keyboard("グループを選んでください。", listVillage);
  int village = keyboard.Open();
  if (village == 0) {
    Keyboard keyboard("フェニーの服を選んでください。", listFenyClothes);
    int choice = keyboard.Open();
    if (choice != -1) {
      Process::Write8(0x83B36C8, choice);
    }
  }
  if (village >= 1) {
    Keyboard keyboard("プーギーの服を選んでください。", listPugyClothes);
    int choice = keyboard.Open();
    if (choice != -1) {
      for (int i = 0; i < 3; i++) {
        if (choice == i) {
          Process::Write8(i * 0x1 + 0x83B36C9, choice + 4);
        }
      }
    }
  }
}

// 酔っぱらい設定
static u8 drunk;
void InstantDrunkOption(MenuEntry *entry) {
  Keyboard keyboard("酔っぱらいになりますか？", listToggle);
  int choice = keyboard.Open();
  if (choice == 0) {
    drunk = 0x02;
  }
  if (choice == 1) {
    drunk = 0x00;
  }
}

// 酔っぱらい
void InstantDrunk(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write8(offset + 0x1510, drunk);
}

// 1回飲んだら酔っぱらい
void Drunk1(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::Write8(offset + 0x1538, 0xA);
}

// 乗りゲージ
void RideGageMax(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8195350, offset);
  Process::WriteFloat(offset + 0x2C18, 2000);
  Process::WriteFloat(offset + 0x2C1C, 1);
}

// 腹減り無効
void HungryInvalid(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8360F24, offset);
  Process::Read32(offset + 0xB4, offset);
  Process::WriteFloat(offset + 0x2DC, 1);
}

void ContrastChange(MenuEntry *entry) {
  float contrast;
  Process::ReadFloat(0x81387A4, contrast);
  Keyboard keyboard(
      Utils::Format("コントラストを入力してください\n現在[%.2f]", contrast));
  keyboard.IsHexadecimal(false);
  keyboard.Open(contrast);
  Process::WriteFloat(0x81387A4, contrast);
}

void InsectTypeChange(MenuEntry *entry) {
  std::vector<std::string> listInsectType{"なし",
                                          "クルドローン",
                                          "アルマスタッグ",
                                          "ガシルドーレ",
                                          "カゼキリバネ",
                                          "モナークブルスタッグ",
                                          "レジナヴォランテ",
                                          "ドゥンクラーブ",
                                          "ウカドゥーレ",
                                          "オオシナト",
                                          "シナトモドキ",
                                          "エルドラーン",
                                          "マルドローン",
                                          "ザミールビートル",
                                          "ハルキータ",
                                          "ガルーヘル",
                                          "ケーニヒゴアビートル",
                                          "フィルカーノ",
                                          "ドルンキータ",
                                          "アルジョアーニャ",
                                          "メイヴァーチル",
                                          "ヴァンリエール",
                                          "アルジャーロン",
                                          "光のルフ",
                                          "バレットホーク",
                                          "とら",
                                          "表示無し"};

  Keyboard keyboard("虫の種類を選んでください。", listInsectType);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(0x8386C68, choice);
  }
}

void InsectLevelChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫のレベルを入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(a);
  Process::Write8(0x8386C69, a);
}

void InsectPowerChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫のパワー補正を0~15で入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C6A, a);
  }
}

void InsectWeightChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫のウェイト補正を0~15で入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C6B, a);
  }
}

void InsectStaminaChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫のスタミナ補正を0~15で入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C6C, a);
  }
}

void InsectFireAttributeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫の火属性を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C6D, a);
  }
}

void InsectWaterAttributeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫の水属性を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C6E, a);
  }
}

void InsectThunderAttributeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫の雷属性を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C6F, a);
  }
}

void InsectIceAttributeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫の氷属性を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C70, a);
  }
}

void InsectDragonAttributeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("虫の龍属性を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8386C71, a);
  }
}

void BaseCreateTargetChange(MenuEntry *entry) {
  Keyboard keyboard("ターゲットを？？？？？にしますか？", listToggle);
  int choice = keyboard.Open();
  if (choice == 0) {
    Process::Write8(0x8487CF3, 0x4C);
  }
}

void BaseCreateQuestTypeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("クエスト形式コードを入力してください。\n20から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CF2, a);
  }
}

void BaseCreateRecruitmentHunterRankMinimumChange(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("募集HRの下限を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x8487CEE, a);
  }
}

void BaseCreateRecruitmentHunterRankMaximumChange(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("募集HRの上限を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x8487CF0, a);
  }
}

void BaseCreateEntryPeopleChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("入室人数コードを入力してください。\n3から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CE9, a);
  }
}

void BaseCreateEntryLimitChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("入室制限コードを入力してください。\n2から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CE8, a);
  }
}

void BaseCreatePasswordExistChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard(
      "パスワード有無コードを入力してください。\n3から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CEC, a);
  }
}

void BaseCreateRecruitmentMessage1Change(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("募集文①コードを入力してください。\n33から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CF4, a);
  }
}

void BaseCreateRecruitmentMessage2Change(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("募集文②コードを入力してください。\n33から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CF5, a);
  }
}

void BaseCreateRecruitmentMessage3Change(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("募集文③コードを入力してください。\n33から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CF6, a);
  }
}

void BaseCreateRecruitmentMessage4Change(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("募集文④コードを入力してください。\n33から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487CF7, a);
  }
}

void BaseSearchTargetChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("ターゲットコードを入力してください。\n76から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487D05, a);
  }
}

void BaseSearchQuestTypeChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("クエスト形式コードを入力してください。\n20から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487D04, a);
  }
}

void BaseSearchHostHunterRankMinimumChange(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("ホストHR下限を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x8487D00, a);
  }
}

void BaseSearchHostHunterRankMaximumChange(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("ホストHR上限を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x8487D02, a);
  }
}

void BaseSearchInQuestChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("クエスト中コードを入力してください。\n2から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487D06, a);
  }
}

void BaseSearchPasswordExistChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard(
      "パスワード有無コードを入力してください。\n2から改造です。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(0x8487D07, a);
  }
}

void HunterArt1Change(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("狩技コードを入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x831B50C, a);
  }
}

void HunterArt2Change(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("狩技コードを入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x831B50E, a);
  }
}

void HunterArt3Change(MenuEntry *entry) {
  u16 a;
  Keyboard keyboard("狩技コードを入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write16(0x831B510, a);
  }
}

void PlayerVoiceChange(MenuEntry *entry) {
  u8 currentVoice;
  std::vector<std::string> listVoiceType{
      "声なし", "TYPE 1", "TYPE 2", "TYPE 3", "TYPE 4", "TYPE 5",
      "TYPE 6", "TYPE 7", "TYPE 8", "TYPE 9", "TYPE 10", "TYPE 11",
      "TYPE 12", "TYPE 13", "TYPE 14", "TYPE 15", "TYPE 16", "TYPE 17",
      "TYPE 18", "TYPE 19", "TYPE 20"};

  Process::Read8(0x831B6ED, currentVoice);
  Keyboard keyboard(
      "声を選んでください。\n現在[" + listVoiceType[currentVoice] + "]",
      listVoiceType);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6ED, choice);
  }
}

void PlayerEyeColorChange(MenuEntry *entry) {
  u8 currentEye;
  std::vector<std::string> listEyeType{"茶色", "赤色", "青色", "黄色",
                                       "緑色", "紫色", "白色", "黒色",
                                       "全部白色", "全部黒色"};

  Process::Read8(0x831B6EE, currentEye);
  Keyboard keyboard(
      "目の色を選んでください。\n現在[" + listEyeType[currentEye] + "]",
      listEyeType);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6EE, choice);
  }
}

void PlayerInnerChange(MenuEntry *entry) {
  u8 currentInner;
  std::vector<std::string> listInnerType{"TYPE 1", "TYPE 2", "TYPE 3", "TYPE 4",
                                         "TYPE 5", "TYPE 6", "TYPE 7"};

  Process::Read8(0x831B6EF, currentInner);
  Keyboard keyboard(
      "インナーを選んでください。\n現在[" + listInnerType[currentInner] + "]",
      listInnerType);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6EF, choice);
  }
}

void PlayerGenderChange(MenuEntry *entry) {
  u8 currentGender;
  std::vector<std::string> listGender{"男", "女"};

  Process::Read8(0x831B6F0, currentGender);
  Keyboard keyboard(
      "性別を選んでください。\n現在[" + listGender[currentGender] + "]",
      listGender);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6F0, choice);
  }
}

void PlayerHuntingStyleChange(MenuEntry *entry) {
  u8 currentHuntingStyle;
  std::vector<std::string> listHuntingStyle{
      "ギルドスタイル", "ストライカースタイル", "エリアルスタイル",
      "ブシドースタイル"};

  Process::Read8(0x831B6F1, currentHuntingStyle);
  Keyboard keyboard("狩猟スタイルを選んでください。\n現在[" +
                        listHuntingStyle[currentHuntingStyle] + "]",
                    listHuntingStyle);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6F1, choice);
  }
}

void PlayerHearStyleChange(MenuEntry *entry) {
  u8 currentHearStyle;
  std::vector<std::string> listHearStyleType{
      "TYPE 1", "TYPE 2", "TYPE 3", "TYPE 4", "TYPE 5", "TYPE 6",
      "TYPE 7", "TYPE 8", "TYPE 9", "TYPE 10", "TYPE 11", "TYPE 12",
      "TYPE 13", "TYPE 14", "TYPE 15", "TYPE 16", "TYPE 17", "TYPE 18",
      "TYPE 19", "TYPE 20", "TYPE 21", "TYPE 22", "TYPE 23", "TYPE 24",
      "TYPE 25", "TYPE 26", "TYPE 27", "TYPE 28", "TYPE 29", "TYPE 30"};

  Process::Read8(0x831B6F2, currentHearStyle);
  Keyboard keyboard("髪型を選んでください。\n現在[" +
                        listHearStyleType[currentHearStyle] + "]",
                    listHearStyleType);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6F2, choice);
  }
}

void PlayerFaceChange(MenuEntry *entry) {
  u8 currentFace;
  std::vector<std::string> listFaceType{
      "TYPE 1", "TYPE 2", "TYPE 3", "TYPE 4", "TYPE 5", "TYPE 6",
      "TYPE 7", "TYPE 8", "TYPE 9", "TYPE 10", "TYPE 11", "TYPE 12",
      "TYPE 13", "TYPE 14", "TYPE 15", "TYPE 16", "TYPE 17", "TYPE 18"};

  Process::Read8(0x831B6F3, currentFace);
  Keyboard keyboard(
      "顔を選んでください。\n現在[" + listFaceType[currentFace] + "]",
      listFaceType);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6F3, choice);
  }
}

void PlayerCosmeticsChange(MenuEntry *entry) {
  u8 currentCosmetics;
  std::vector<std::string> listMakeType{
      "TYPE 1", "TYPE 2", "TYPE 3", "TYPE 4", "TYPE 5",
      "TYPE 6", "TYPE 7", "TYPE 8", "TYPE 9", "TYPE 10",
      "TYPE 11", "TYPE 12", "TYPE 13", "TYPE 14", "メイクなし"};

  Process::Read8(0x831B6F4, currentCosmetics);
  Keyboard keyboard(
      "メイクを選んでください。\n現在[" + listMakeType[currentCosmetics] + "]",
      listMakeType);
  int choice = keyboard.Open();
  if (choice != -1) {
    Process::Write8(0x831B6F4, choice);
  }
}

void TitleID() {
  std::string tid;
  Process::GetTitleID(tid);
  MessageBox("タイトルIDは " + tid + " です。")();
}

void ProcessNameID() {
  std::string name;
  Process::GetName(name);
  MessageBox("プロセスの名前は " + name + " です。")();
}

void ConsoleType() {
  switch (System::IsNew3DS()) {
    case 0:MessageBox("Old3DSです。")();
      break;
    case 1:MessageBox("New3DSです。")();
      break;
  }
}

void WiFiStatus() {
  switch (System::IsConnectedToInternet()) {
    case 0:MessageBox("WiFiに接続されていません。")();
      break;
    case 1:MessageBox("WiFiに接続されています。")();
      break;
  }
}

Handle mcuhwcHandle;

Result mcuInit() { return srvGetServiceHandle(&mcuhwcHandle, "mcu::HWC"); }

Result mcuExit() { return svcCloseHandle(mcuhwcHandle); }

Result mcuGetBatteryLevel(u8 *out) {
  u32 *ipc = getThreadCommandBuffer();
  ipc[0] = 0x50000;
  Result ret = svcSendSyncRequest(mcuhwcHandle);
  if (ret < 0) return ret;
  *out = ipc[2];
  return ipc[1];
}

void BatteryLevel() {
  // u8 percent = 0;
  // MCUHWC_GetBatteryLevel(&percent);
  // std::string percent_string = std::to_string(percent) + "%";
  // MessageBox("バッテリー残量は" + percent_string + "です。")();

  // static float batteryPercentage;
  // Result res = 0;
  // u8 data[4];
  // res = MCUHWC_ReadRegister(0xA, data, 4);
  // batteryPercentage = data[1] + data[2] / 256.0f;
  // batteryPercentage = (u32)((batteryPercentage + 0.05f) * 10.0f) / 10.0f;
  // MessageBox(Utils::Format("バッテリー残量は%3.fです。",
  // batteryPercentage))();

  u8 batteryPercentage;
  mcuInit();
  mcuGetBatteryLevel(&batteryPercentage);
  mcuExit();
  MessageBox(Utils::Format("バッテリー残量は%d%%です。", batteryPercentage))();
}

void Information(MenuEntry *entry) {
  StringVector info{"タイトルID", "プロセスの名前", "3DSのタイプ",
                    "Wi-Fi接続確認", "バッテリー残量確認"};

  Keyboard keyboard("確認したい情報を選んでください。", info);
  int choice = keyboard.Open();

  switch (choice) {
    case 0:TitleID();
      break;
    case 1:ProcessNameID();
      break;
    case 2:ConsoleType();
      break;
    case 3:WiFiStatus();
      break;
    case 4:BatteryLevel();
      break;
  }
}

void HexToDecd32(MenuEntry *entry) {
  u32 out;
  Keyboard keyboard(
      "16進数を入力してください。\n-に対応しています。\n例:FFFFFFFF = -1");
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %d です。", (s32) out))();
  }
}

void HexToDecu32(MenuEntry *entry) {
  u32 out;
  Keyboard keyboard(
      "16進数を入力してください。\n-に対応していません。\n例:FFFFFFFF = "
      "4294967295");
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %u です。", out))();
  }
}

void HexToDecd16(MenuEntry *entry) {
  u16 out;
  Keyboard keyboard(
      "16進数を入力してください。\n-に対応しています。\n例:FFFF = -1");
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %d です。", (s16) out))();
  }
}

void HexToDecu16(MenuEntry *entry) {
  u16 out;
  Keyboard keyboard(
      "16進数を入力してください。\n-に対応していません。\n例:FFFF = 65535");
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %u です。", out))();
  }
}

void HexToDecd8(MenuEntry *entry) {
  u8 out;
  Keyboard keyboard(
      "16進数を入力してください。\n-に対応しています。\n例:FF = -1");
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %d です。", (s8) out))();
  }
}

void HexToDecu8(MenuEntry *entry) {
  u8 out;
  Keyboard keyboard(
      "16進数を入力してください。\n-に対応していません。\n例:FF = 255");
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %u です。", out))();
  }
}

void DecToHex(MenuEntry *entry) {
  u32 out;
  Keyboard keyboard("10進数を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(out) != -1) {
    MessageBox(Utils::Format("結果は %X です。", out))();
  }
}

void HexadecimalCalculator(MenuEntry *entry) {
  u32 data;
  int hex1, hex2, ans, choice;
  Keyboard keyboard("1番目の16進数を入力してください。");
  if (keyboard.Open(data) != -1) {
    hex1 = data;
    Keyboard keyboard("算術演算子を選んでください。", {"+", "-", "×", "÷"});
    choice = keyboard.Open();
    if (choice != -1) {
      Keyboard keyboard("2番目の16進数を入力してください。");
      if (keyboard.Open(data) != -1) {
        hex2 = data;
        if (choice == 0) {
          ans = hex1 + hex2;
        }
        if (choice == 1) {
          ans = hex1 - hex2;
        }
        if (choice == 2) {
          ans = hex1 * hex2;
        }
        if (choice == 3) {
          ans = hex1 / hex2;
        }
        MessageBox(Utils::Format("結果は %X です。", ans))();
      }
    }
  }
}

void DecimalCalculator(MenuEntry *entry) {
  u32 data;
  int dec1, dec2, ans, choice;
  Keyboard keyboard("1番目の10進数を入力してください。");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(data) != -1) {
    dec1 = data;
    Keyboard keyboard("算術演算子を選んでください。", {"+", "-", "×", "÷"});
    choice = keyboard.Open();
    if (choice != -1) {
      Keyboard keyboard("2番目の10進数を入力してください。");
      keyboard.IsHexadecimal(false);
      if (keyboard.Open(data) != -1) {
        dec2 = data;
        if (choice == 0) {
          ans = dec1 + dec2;
        }
        if (choice == 1) {
          ans = dec1 - dec2;
        }
        if (choice == 2) {
          ans = dec1 * dec2;
        }
        if (choice == 3) {
          ans = dec1 / dec2;
        }
        MessageBox(Utils::Format("結果は %d です。", ans))();
      }
    }
  }
}

void DoubleCalculator(MenuEntry *entry) {
  int choice;
  double double1, double2, ans;
  Keyboard keyboard("1番目の浮動小数点数を入力してください。");
  if (keyboard.Open(double1) != -1) {
    Keyboard keyboard("算術演算子を選んでください。", {"+", "-", "×", "÷"});
    choice = keyboard.Open();
    if (choice != -1) {
      Keyboard keyboard("2番目の浮動小数点数を入力してください。");
      if (keyboard.Open(double2) != -1) {
        if (choice == 0) {
          ans = double1 + double2;
        }
        if (choice == 1) {
          ans = double1 - double2;
        }
        if (choice == 2) {
          ans = double1 * double2;
        }
        if (choice == 3) {
          ans = double1 / double2;
        }
        MessageBox(Utils::Format("結果は %f です。", ans))();
      }
    }
  }
}

// 変換候補変換
void ChatConversionChange(MenuEntry *entry) {
  u32 a, b, c, aaa, bbb, ccc;
  std::string character1, character2, character3;
  aaa = a = 0xF8;
  bbb = b + 0xF8;
  ccc = c + 0xF8;
  Process::Read32(0x878CF80, a);
  Process::Read32(0x8790F80, b);
  Process::Read32(0x8791F80, c);
  Process::ReadString(a + 0x18, character1, 12, StringFormat::Utf16);
  Process::ReadString(b + 0x18, character2, 12, StringFormat::Utf16);
  Process::ReadString(c + 0x18, character3, 12, StringFormat::Utf16);
  if (Controller::IsKeysDown(R)) {
    if (character1 == "るーと")
      Process::WriteString(aaa, "√", StringFormat::Utf16);
    if (character2 == "るーと")
      Process::WriteString(bbb, "√", StringFormat::Utf16);
    if (character3 == "るーと")
      Process::WriteString(ccc, "√", StringFormat::Utf16);
    if (character1 == "まるいち")
      Process::WriteString(aaa, "①", StringFormat::Utf16);
    if (character2 == "まるいち")
      Process::WriteString(bbb, "①", StringFormat::Utf16);
    if (character3 == "まるいち")
      Process::WriteString(ccc, "①", StringFormat::Utf16);
    if (character1 == "まるに")
      Process::WriteString(aaa, "②", StringFormat::Utf16);
    if (character2 == "まるに")
      Process::WriteString(bbb, "②", StringFormat::Utf16);
    if (character3 == "まるに")
      Process::WriteString(ccc, "②", StringFormat::Utf16);
    if (character1 == "まるさん")
      Process::WriteString(aaa, "③", StringFormat::Utf16);
    if (character2 == "まるさん")
      Process::WriteString(bbb, "③", StringFormat::Utf16);
    if (character3 == "まるさん")
      Process::WriteString(ccc, "③", StringFormat::Utf16);
    if (character1 == "まるよん")
      Process::WriteString(aaa, "④", StringFormat::Utf16);
    if (character2 == "まるよん")
      Process::WriteString(bbb, "④", StringFormat::Utf16);
    if (character3 == "まるよん")
      Process::WriteString(ccc, "④", StringFormat::Utf16);
    if (character1 == "まるご")
      Process::WriteString(aaa, "⑤", StringFormat::Utf16);
    if (character2 == "まるご")
      Process::WriteString(bbb, "⑤", StringFormat::Utf16);
    if (character3 == "まるご")
      Process::WriteString(ccc, "⑤", StringFormat::Utf16);
    if (character1 == "まるろく")
      Process::WriteString(aaa, "⑥", StringFormat::Utf16);
    if (character2 == "まるろく")
      Process::WriteString(bbb, "⑥", StringFormat::Utf16);
    if (character3 == "まるろく")
      Process::WriteString(ccc, "⑥", StringFormat::Utf16);
    if (character1 == "まるなな")
      Process::WriteString(aaa, "⑦", StringFormat::Utf16);
    if (character2 == "まるなな")
      Process::WriteString(bbb, "⑦", StringFormat::Utf16);
    if (character3 == "まるなな")
      Process::WriteString(ccc, "⑦", StringFormat::Utf16);
    if (character1 == "まるはち")
      Process::WriteString(aaa, "⑧", StringFormat::Utf16);
    if (character2 == "まるはち")
      Process::WriteString(bbb, "⑧", StringFormat::Utf16);
    if (character3 == "まるはち")
      Process::WriteString(ccc, "⑧", StringFormat::Utf16);
    if (character1 == "まるきゅう")
      Process::WriteString(aaa, "⑨", StringFormat::Utf16);
    if (character2 == "まるきゅう")
      Process::WriteString(bbb, "⑨", StringFormat::Utf16);
    if (character3 == "まるきゅう")
      Process::WriteString(ccc, "⑨", StringFormat::Utf16);
    if (character1 == "えす")
      Process::WriteString(aaa, "∫", StringFormat::Utf16);
    if (character2 == "えす")
      Process::WriteString(bbb, "∫", StringFormat::Utf16);
    if (character3 == "えす")
      Process::WriteString(ccc, "∫", StringFormat::Utf16);
    if (character1 == "だぶるえす")
      Process::WriteString(aaa, "∬", StringFormat::Utf16);
    if (character2 == "だぶるえす")
      Process::WriteString(bbb, "∬", StringFormat::Utf16);
    if (character3 == "だぶるえす")
      Process::WriteString(ccc, "∬", StringFormat::Utf16);
    if (character1 == "ろーまいち")
      Process::WriteString(aaa, "Ⅰ", StringFormat::Utf16);
    if (character2 == "ろーまいち")
      Process::WriteString(bbb, "Ⅰ", StringFormat::Utf16);
    if (character3 == "ろーまいち")
      Process::WriteString(ccc, "Ⅰ", StringFormat::Utf16);
    if (character1 == "ろーまに")
      Process::WriteString(aaa, "Ⅱ", StringFormat::Utf16);
    if (character2 == "ろーまに")
      Process::WriteString(bbb, "Ⅱ", StringFormat::Utf16);
    if (character3 == "ろーまに")
      Process::WriteString(ccc, "Ⅱ", StringFormat::Utf16);
    if (character1 == "ろーまさん")
      Process::WriteString(aaa, "Ⅲ", StringFormat::Utf16);
    if (character2 == "ろーまさん")
      Process::WriteString(bbb, "Ⅲ", StringFormat::Utf16);
    if (character3 == "ろーまさん")
      Process::WriteString(ccc, "Ⅲ", StringFormat::Utf16);
    if (character1 == "ろーまよん")
      Process::WriteString(aaa, "Ⅳ", StringFormat::Utf16);
    if (character2 == "ろーまよん")
      Process::WriteString(bbb, "Ⅳ", StringFormat::Utf16);
    if (character3 == "ろーまよん")
      Process::WriteString(ccc, "Ⅳ", StringFormat::Utf16);
    if (character1 == "ろーまご")
      Process::WriteString(aaa, "Ⅴ", StringFormat::Utf16);
    if (character2 == "ろーまご")
      Process::WriteString(bbb, "Ⅴ", StringFormat::Utf16);
    if (character3 == "ろーまご")
      Process::WriteString(ccc, "Ⅴ", StringFormat::Utf16);
    if (character1 == "ろーまろく")
      Process::WriteString(aaa, "Ⅵ", StringFormat::Utf16);
    if (character2 == "ろーまろく")
      Process::WriteString(bbb, "Ⅵ", StringFormat::Utf16);
    if (character3 == "ろーまろく")
      Process::WriteString(ccc, "Ⅵ", StringFormat::Utf16);
    if (character1 == "ろーまなな")
      Process::WriteString(aaa, "Ⅶ", StringFormat::Utf16);
    if (character2 == "ろーまなな")
      Process::WriteString(bbb, "Ⅶ", StringFormat::Utf16);
    if (character3 == "ろーまなな")
      Process::WriteString(ccc, "Ⅶ", StringFormat::Utf16);
    if (character1 == "ろーまはち")
      Process::WriteString(aaa, "Ⅷ", StringFormat::Utf16);
    if (character2 == "ろーまはち")
      Process::WriteString(bbb, "Ⅷ", StringFormat::Utf16);
    if (character3 == "ろーまはち")
      Process::WriteString(ccc, "Ⅷ", StringFormat::Utf16);
    if (character1 == "ろーまきゅう")
      Process::WriteString(aaa, "Ⅸ", StringFormat::Utf16);
    if (character2 == "ろーまきゅう")
      Process::WriteString(bbb, "Ⅸ", StringFormat::Utf16);
    if (character3 == "ろーまきゅう")
      Process::WriteString(ccc, "Ⅸ", StringFormat::Utf16);
    if (character1 == "ろーまじゅう")
      Process::WriteString(aaa, "Ⅹ", StringFormat::Utf16);
    if (character2 == "ろーまじゅう")
      Process::WriteString(bbb, "Ⅹ", StringFormat::Utf16);
    if (character3 == "ろーまじゅう")
      Process::WriteString(ccc, "Ⅹ", StringFormat::Utf16);
    if (character1 == "みり")
      Process::WriteString(aaa, "㍉", StringFormat::Utf16);
    if (character2 == "みり")
      Process::WriteString(bbb, "㍉", StringFormat::Utf16);
    if (character3 == "みり")
      Process::WriteString(ccc, "㍉", StringFormat::Utf16);
    if (character1 == "きろ")
      Process::WriteString(aaa, "㌔", StringFormat::Utf16);
    if (character2 == "きろ")
      Process::WriteString(bbb, "㌔", StringFormat::Utf16);
    if (character3 == "きろ")
      Process::WriteString(ccc, "㌔", StringFormat::Utf16);
    if (character1 == "せんち")
      Process::WriteString(aaa, "㌢", StringFormat::Utf16);
    if (character2 == "せんち")
      Process::WriteString(bbb, "㌢", StringFormat::Utf16);
    if (character3 == "せんち")
      Process::WriteString(ccc, "㌢", StringFormat::Utf16);
    if (character1 == "めーとる")
      Process::WriteString(aaa, "㍍", StringFormat::Utf16);
    if (character2 == "めーとる")
      Process::WriteString(bbb, "㍍", StringFormat::Utf16);
    if (character3 == "めーとる")
      Process::WriteString(ccc, "㍍", StringFormat::Utf16);
    if (character1 == "ぐらむ")
      Process::WriteString(aaa, "㌘", StringFormat::Utf16);
    if (character2 == "ぐらむ")
      Process::WriteString(bbb, "㌘", StringFormat::Utf16);
    if (character3 == "ぐらむ")
      Process::WriteString(ccc, "㌘", StringFormat::Utf16);
    if (character1 == "とん")
      Process::WriteString(aaa, "㌧", StringFormat::Utf16);
    if (character2 == "とん")
      Process::WriteString(bbb, "㌧", StringFormat::Utf16);
    if (character3 == "とん")
      Process::WriteString(ccc, "㌧", StringFormat::Utf16);
    if (character1 == "あーる")
      Process::WriteString(aaa, "㌃", StringFormat::Utf16);
    if (character2 == "あーる")
      Process::WriteString(bbb, "㌃", StringFormat::Utf16);
    if (character3 == "あーる")
      Process::WriteString(ccc, "㌃", StringFormat::Utf16);
    if (character1 == "へくたーる")
      Process::WriteString(aaa, "㌶", StringFormat::Utf16);
    if (character2 == "へくたーる")
      Process::WriteString(bbb, "㌶", StringFormat::Utf16);
    if (character3 == "へくたーる")
      Process::WriteString(ccc, "㌶", StringFormat::Utf16);
    if (character1 == "りっとる")
      Process::WriteString(aaa, "㍑", StringFormat::Utf16);
    if (character2 == "りっとる")
      Process::WriteString(bbb, "㍑", StringFormat::Utf16);
    if (character3 == "りっとる")
      Process::WriteString(ccc, "㍑", StringFormat::Utf16);
    if (character1 == "わっと")
      Process::WriteString(aaa, "㍗", StringFormat::Utf16);
    if (character2 == "わっと")
      Process::WriteString(bbb, "㍗", StringFormat::Utf16);
    if (character3 == "わっと")
      Process::WriteString(ccc, "㍗", StringFormat::Utf16);
    if (character1 == "かろりー")
      Process::WriteString(aaa, "㌍", StringFormat::Utf16);
    if (character2 == "かろりー")
      Process::WriteString(bbb, "㌍", StringFormat::Utf16);
    if (character3 == "かろりー")
      Process::WriteString(ccc, "㌍", StringFormat::Utf16);
    if (character1 == "どる")
      Process::WriteString(aaa, "㌦", StringFormat::Utf16);
    if (character2 == "どる")
      Process::WriteString(bbb, "㌦", StringFormat::Utf16);
    if (character3 == "どる")
      Process::WriteString(ccc, "㌦", StringFormat::Utf16);
    if (character1 == "せんと")
      Process::WriteString(aaa, "㌣", StringFormat::Utf16);
    if (character2 == "せんと")
      Process::WriteString(bbb, "㌣", StringFormat::Utf16);
    if (character3 == "せんと")
      Process::WriteString(ccc, "㌣", StringFormat::Utf16);
    if (character1 == "ぱーせんと")
      Process::WriteString(aaa, "㌫", StringFormat::Utf16);
    if (character2 == "ぱーせんと")
      Process::WriteString(bbb, "㌫", StringFormat::Utf16);
    if (character3 == "ぱーせんと")
      Process::WriteString(ccc, "㌫", StringFormat::Utf16);
    if (character1 == "みりばーる")
      Process::WriteString(aaa, "㍊", StringFormat::Utf16);
    if (character2 == "みりばーる")
      Process::WriteString(bbb, "㍊", StringFormat::Utf16);
    if (character3 == "みりばーる")
      Process::WriteString(ccc, "㍊", StringFormat::Utf16);
    if (character1 == "ぺーじ")
      Process::WriteString(aaa, "㌻", StringFormat::Utf16);
    if (character2 == "ぺーじ")
      Process::WriteString(bbb, "㌻", StringFormat::Utf16);
    if (character3 == "ぺーじ")
      Process::WriteString(ccc, "㌻", StringFormat::Utf16);
    if (character1 == "へいせい")
      Process::WriteString(aaa, "㍻", StringFormat::Utf16);
    if (character2 == "へいせい")
      Process::WriteString(bbb, "㍻", StringFormat::Utf16);
    if (character3 == "へいせい")
      Process::WriteString(ccc, "㍻", StringFormat::Utf16);
    if (character1 == "しょうわ")
      Process::WriteString(aaa, "㍼", StringFormat::Utf16);
    if (character2 == "しょうわ")
      Process::WriteString(bbb, "㍼", StringFormat::Utf16);
    if (character3 == "しょうわ")
      Process::WriteString(ccc, "㍼", StringFormat::Utf16);
    if (character1 == "たいしょう")
      Process::WriteString(aaa, "㍽", StringFormat::Utf16);
    if (character2 == "たいしょう")
      Process::WriteString(bbb, "㍽", StringFormat::Utf16);
    if (character3 == "たいしょう")
      Process::WriteString(ccc, "㍽", StringFormat::Utf16);
    if (character1 == "めいじ")
      Process::WriteString(aaa, "㍾", StringFormat::Utf16);
    if (character2 == "めいじ")
      Process::WriteString(bbb, "㍾", StringFormat::Utf16);
    if (character3 == "めいじ")
      Process::WriteString(ccc, "㍾", StringFormat::Utf16);
    if (character1 == "なんばー")
      Process::WriteString(aaa, "№", StringFormat::Utf16);
    if (character2 == "なんばー")
      Process::WriteString(bbb, "№", StringFormat::Utf16);
    if (character3 == "なんばー")
      Process::WriteString(ccc, "№", StringFormat::Utf16);
    if (character1 == "けーけー")
      Process::WriteString(aaa, "㏍", StringFormat::Utf16);
    if (character2 == "けーけー")
      Process::WriteString(bbb, "㏍", StringFormat::Utf16);
    if (character3 == "けーけー")
      Process::WriteString(ccc, "㏍", StringFormat::Utf16);
    if (character1 == "てる")
      Process::WriteString(aaa, "℡", StringFormat::Utf16);
    if (character2 == "てる")
      Process::WriteString(bbb, "℡", StringFormat::Utf16);
    if (character3 == "てる")
      Process::WriteString(ccc, "℡", StringFormat::Utf16);
    if (character1 == "たぶ")
      Process::WriteString(aaa, "\t", StringFormat::Utf16);
    if (character2 == "たぶ")
      Process::WriteString(bbb, "\t", StringFormat::Utf16);
    if (character3 == "たぶ")
      Process::WriteString(ccc, "\t", StringFormat::Utf16);
    if (character1 == "かいぎょう")
      Process::WriteString(aaa, "\n", StringFormat::Utf16);
    if (character2 == "かいぎょう")
      Process::WriteString(bbb, "\n", StringFormat::Utf16);
    if (character3 == "かいぎょう")
      Process::WriteString(ccc, "\n", StringFormat::Utf16);
    if (character1 == "こう")
      Process::WriteString(aaa, "爻", StringFormat::Utf16);
    if (character2 == "こう")
      Process::WriteString(bbb, "爻", StringFormat::Utf16);
    if (character3 == "こう")
      Process::WriteString(ccc, "爻", StringFormat::Utf16);

    //	if(character1 == "") Process::WriteString(aa, "",
    // StringFormat::Utf16); 	if(character2 == "")
    // Process::WriteString(bb,
    //"", StringFormat::Utf16); 	if(character3 == "")
    // Process::WriteString(cc, "", StringFormat::Utf16);
  }
}

// 変換候補変換可能文字一覧
void ChatConversionList(MenuEntry *entry) {
  std::vector<std::string> listChatConversion{"るーと √",
                                              "えす ∫",
                                              "だぶるえす ∬",
                                              "なんばー №",
                                              "けーけー ㏍",
                                              "てる ℡",
                                              "こう 爻",
                                              "まる(数字) ① ②",
                                              "ろーま(数字) Ⅰ Ⅱ",
                                              "(単位) ㌔ ㍍",
                                              "(元号) ㍻ ㍼",
                                              "かいぎょう",
                                              "たぶ",
                                              "どんどん追加してくよ！"};

  Keyboard keyboard(
      "変換候補変換可能文字一覧です。\n"
      "(数字)と書かれている所は、いち、に、等の数字を書いてください。\n"
      "(単位)"
      "と書かれている所は、きろ、や、めーとる、等の単位を書いてください。\n"
      "(元号)"
      "と書かれている所は、へいせい、や、しょうわ、等の元号を書いてください。"
      "\n"
      "改行はキーボード上では表示されますが、チャットログだと空白が表示されま"
      "す"
      "。\n"
      "一部変換できない文字があります。",
      listChatConversion);
  keyboard.Open();
}

static int palicoChoice;
void PalicoChoice(MenuEntry *entry) {
  std::string name[60];
  std::vector<std::string> nameSave;

  nameSave.clear();
  for (int i = 0; i < 60; i++) {
    Process::ReadString(i * 0x494 + 0x8338AFE, name[i], 30, StringFormat::Utf8);
    nameSave.push_back(name[i]);
  }
  Keyboard keyboard("ねこを選択してください。", nameSave);
  if (keyboard.Open() != -1) {
    palicoChoice = keyboard.Open();
  }
}

void PalicoExperienceChange(MenuEntry *entry) {
  u32 exp;
  Process::Read32(palicoChoice * 0x494 + 0x83388E0, exp);
  Keyboard keyboard(Utils::Format("経験値を入力してください。\n現在[%d]", exp));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(exp) != -1) {
    Process::Write32(palicoChoice * 0x494 + 0x83388E0, exp);
  }
}

void PalicoLevelChange(MenuEntry *entry) {
  u8 lv, levelDisplay;
  Process::Read8(palicoChoice * 0x494 + 0x83388E4, lv);
  levelDisplay = lv + 1;
  Keyboard keyboard(Utils::Format(
      "レベルを入力してください。\n50までで設定してください。\n現在[%d]",
      levelDisplay));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(lv) != -1) {
    Process::Write8(palicoChoice * 0x494 * 0x83388E4, lv);
  }
}

void PalicoSupportTrendChange(MenuEntry *entry) {
  u8 sup;
  std::vector<std::string> listPalicoSupportTrend{
      "カリスマ", "ファイト", "ガード", "アシスト",
      "回復", "ボマー", "��レクト"};
  Process::Read8(palicoChoice * 0x494 + 0x83388E5, sup);
  Keyboard keyboard("サポート傾向を選んでください。\n現在[" +
                        listPalicoSupportTrend[sup] + "]",
                    listPalicoSupportTrend);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388E5, choice);
  }
}

void PalicoClosenessChange(MenuEntry *entry) {
  u8 closeness;
  Process::Read8(palicoChoice * 0x494 + 0x83388E6, closeness);
  Keyboard keyboard(
      Utils::Format("親密度を入力してください。\n現在[%d]", closeness));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(closeness) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388E6, closeness);
  }
}

void PalicoTargetChange(MenuEntry *entry) {
  u8 tar;
  std::vector<std::string> listPalicoTarget{"指定なし", "小型一筋", "小型優先",
                                            "バランス", "大型優先", "大型一筋"};
  Process::Read8(palicoChoice * 0x494 + 0x83388E7, tar);
  Keyboard keyboard(
      "ターゲットを選んでください。\n現在[" + listPalicoTarget[tar] + "]",
      listPalicoTarget);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388E7, choice);
  }
}

void PalicoCommentEditPossibleChange(MenuEntry *entry) {
  u8 comment;
  std::string ko;
  Process::Read8(palicoChoice * 0x494 + 0x83389A0, comment);
  if (comment < 0x80) {
    ko = "可能";
  }
  if (comment >= 0x80) {
    ko = "不可能";
  }
  Keyboard keyboard(
      "オトモコメントを編集可能にしますか？。\n現在[オトモコメント編集" + ko +
          "]",
      listToggle);
  if (int choice = keyboard.Open() != -1) {
    if (choice == 0) {
      Process::Write8(palicoChoice * 0x494 + 0x83389A0, 0x20);
    }
    if (choice == 1) {
      Process::Write8(palicoChoice * 0x494 + 0x83389A0, 0xA0);
    }
  }
}

void SpecialDeliveryDisplayChange(MenuEntry *entry) {
  u8 isSpecial;
  std::string to;
  Process::Read8(palicoChoice * 0x494 + 0x83389A1, isSpecial);
  if (isSpecial == 0) {
    to = "特別配信表示じゃない";
  }
  if (isSpecial == 1) {
    to = "特別配信表示";
  }
  Keyboard keyboard("特別配信表示にしますか？\n現在[" + to + "]", listToggle);
  if (int choice = keyboard.Open() != -1) {
    if (choice == 0) {
      Process::Write8(palicoChoice * 0x494 + 0x83389A1, 0x1);
    }
    if (choice == 1) {
      Process::Write8(palicoChoice * 0x494 + 0x83389A1, 0x0);
    }
  }
}

void PalicoEquipmentSupportAction1Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388E8, sup);
  Keyboard keyboard("1番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388E8, choice);
  }
}

void PalicoEquipmentSupportAction2Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388E9, sup);
  Keyboard keyboard("2番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388E9, choice);
  }
}

void PalicoEquipmentSupportAction3Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388EA, sup);
  Keyboard keyboard("3番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388EA, choice);
  }
}

void PalicoEquipmentSupportAction4Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388EB, sup);
  Keyboard keyboard("4番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388EB, choice);
  }
}

void PalicoEquipmentSupportAction5Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388EC, sup);
  Keyboard keyboard("5番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388EC, choice);
  }
}

void PalicoEquipmentSupportAction6Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388ED, sup);
  Keyboard keyboard("6番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388ED, choice);
  }
}

void PalicoEquipmentSupportAction7Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388EE, sup);
  Keyboard keyboard("7番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388EE, choice);
  }
}

void PalicoEquipmentSupportAction8Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388EF, sup);
  Keyboard keyboard("8番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388EF, choice);
  }
}

void PalicoEquipmentSkill1Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F0, ski);
  Keyboard keyboard("1番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F0, choice);
  }
}

void PalicoEquipmentSkill2Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F1, ski);
  Keyboard keyboard("2番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F1, choice);
  }
}

void PalicoEquipmentSkill3Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F2, ski);
  Keyboard keyboard("3番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F2, choice);
  }
}

void PalicoEquipmentSkill4Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F3, ski);
  Keyboard keyboard("4番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F3, choice);
  }
}

void PalicoEquipmentSkill5Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F4, ski);
  Keyboard keyboard("5番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F4, choice);
  }
}

void PalicoEquipmentSkill6Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F5, ski);
  Keyboard keyboard("6番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F5, choice);
  }
}

void PalicoEquipmentSkill7Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F6, ski);
  Keyboard keyboard("7番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F6, choice);
  }
}

void PalicoEquipmentSkill8Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x83388F7, ski);
  Keyboard keyboard("8番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F7, choice);
  }
}

void PalicoLearnSupportAction1Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388F8, sup);
  Keyboard keyboard("1番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F8, choice);
  }
}

void PalicoLearnSupportAction2Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388F9, sup);
  Keyboard keyboard("2番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388F9, choice);
  }
}

void PalicoLearnSupportAction3Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388FA, sup);
  Keyboard keyboard("3番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388FA, choice);
  }
}

void PalicoLearnSupportAction4Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388FB, sup);
  Keyboard keyboard("4番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388FB, choice);
  }
}

void PalicoLearnSupportAction5Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388FC, sup);
  Keyboard keyboard("5番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388FC, choice);
  }
}

void PalicoLearnSupportAction6Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388FD, sup);
  Keyboard keyboard("6番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388FD, choice);
  }
}

void PalicoLearnSupportAction7Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388FE, sup);
  Keyboard keyboard("7番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388FE, choice);
  }
}

void PalicoLearnSupportAction8Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x83388FF, sup);
  Keyboard keyboard("8番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x83388FF, choice);
  }
}

void PalicoLearnSupportAction9Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338900, sup);
  Keyboard keyboard("9番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338900, choice);
  }
}

void PalicoLearnSupportAction10Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338901, sup);
  Keyboard keyboard("10番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338901, choice);
  }
}

void PalicoLearnSupportAction11Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338902, sup);
  Keyboard keyboard("11番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338902, choice);
  }
}

void PalicoLearnSupportAction12Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338903, sup);
  Keyboard keyboard("12番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338903, choice);
  }
}

void PalicoLearnSupportAction13Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338904, sup);
  Keyboard keyboard("13番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338904, choice);
  }
}

void PalicoLearnSupportAction14Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338905, sup);
  Keyboard keyboard("14番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338905, choice);
  }
}

void PalicoLearnSupportAction15Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338906, sup);
  Keyboard keyboard("15番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338906, choice);
  }
}

void PalicoLearnSupportAction16Change(MenuEntry *entry) {
  u8 sup;
  Process::Read8(palicoChoice * 0x494 + 0x8338907, sup);
  Keyboard keyboard("16番目のサポート行動を選んでください。\n現在[" +
                        listPalicoAction[sup] + "]",
                    listPalicoAction);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338907, choice);
  }
}

void PalicoLearnSupportSkill1Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x8338908, ski);
  Keyboard keyboard("1番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338908, choice);
  }
}

void PalicoLearnSupportSkill2Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x8338909, ski);
  Keyboard keyboard("2番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338909, choice);
  }
}

void PalicoLearnSupportSkill3Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x833890A, ski);
  Keyboard keyboard("3番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x833890A, choice);
  }
}

void PalicoLearnSupportSkill4Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x833890B, ski);
  Keyboard keyboard("4番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x833890B, choice);
  }
}

void PalicoLearnSupportSkill5Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x833890C, ski);
  Keyboard keyboard("5番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x833890C, choice);
  }
}

void PalicoLearnSupportSkill6Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x833890D, ski);
  Keyboard keyboard("6番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x833890D, choice);
  }
}

void PalicoLearnSupportSkill7Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x833890E, ski);
  Keyboard keyboard("7番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x833890E, choice);
  }
}

void PalicoLearnSupportSkill8Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x833890F, ski);
  Keyboard keyboard("8番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x833890F, choice);
  }
}

void PalicoLearnSupportSkill9Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x8338910, ski);
  Keyboard keyboard("9番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338910, choice);
  }
}

void PalicoLearnSupportSkill10Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x8338911, ski);
  Keyboard keyboard("10番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338911, choice);
  }
}

void PalicoLearnSupportSkill11Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x8338912, ski);
  Keyboard keyboard("11番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338912, choice);
  }
}

void PalicoLearnSupportSkill12Change(MenuEntry *entry) {
  u8 ski;
  Process::Read8(palicoChoice * 0x494 + 0x8338913, ski);
  Keyboard keyboard("12番目のオトモスキルを選んでください。\n現在[" +
                        listPalicoSkill[ski] + "]",
                    listPalicoSkill);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338913, choice);
  }
}

void PalicoVoiceChange(MenuEntry *entry) {
  u8 voice;
  std::vector<std::string> listPalicoVoice{"なし", "TYPE1", "TYPE2", "TYPE3"};
  Process::Read8(palicoChoice * 0x494 + 0x8338AC1, voice);
  Keyboard keyboard(
      "声を選んでください。\n現在[" + listPalicoVoice[voice] + "]",
      listPalicoVoice);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AC1, choice);
  }
}

void PalicoEyeChange(MenuEntry *entry) {
  u8 eye;
  std::vector<std::string> listPalicoEye{"ふつう",
                                         "ほそ目",
                                         "つり目",
                                         "ニヤケ目",
                                         "閉じ目",
                                         "キズ目"
                                         "透明"};
  Process::Read8(palicoChoice * 0x494 + 0x8338AC2, eye);
  Keyboard keyboard("目を選んでください。\n現在[" + listPalicoEye[eye] + "]",
                    listPalicoEye);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AC2, choice);
  }
}

void PalicoInnerChange(MenuEntry *entry) {
  u8 inner;
  std::vector<std::string> listPalicoInner{"TYPE1", "TYPE2", "ファラオ",
                                           "ゴア", "シャガル", "透明"};
  Process::Read8(palicoChoice * 0x494 + 0x8338AC3, inner);
  Keyboard keyboard(
      "インナーを選んでください。\n現在[" + listPalicoInner[inner] + "]",
      listPalicoInner);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AC3, choice);
  }
}

void PalicoFurCoatChange(MenuEntry *entry) {
  u8 kenami;
  std::vector<std::string> listPalicoFurCoat{
      "アイルー", "メラルー", "アメショ", "ワントーン",
      "ツートーン", "ミケ", "ハンテン"};
  Process::Read8(palicoChoice * 0x494 + 0x8338AC6, kenami);
  Keyboard keyboard(
      "毛並みを選んでください。\n現在[" + listPalicoFurCoat[kenami] + "]",
      listPalicoFurCoat);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AC6, choice);
  }
}

void PalicoEarChange(MenuEntry *entry) {
  u8 mimi;
  std::vector<std::string> listPalicoEar{"ふつう", "たれ耳", "聞き耳",
                                         "立ち耳", "まる耳", "透明"};
  Process::Read8(palicoChoice * 0x494 + 0x8338AC7, mimi);
  Keyboard keyboard("耳を選んでください。\n現在[" + listPalicoEar[mimi] + "]",
                    listPalicoEar);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AC7, choice);
  }
}

void PalicoTailChange(MenuEntry *entry) {
  u8 tail;
  std::vector<std::string> listPalicoTail{"ふつう", "ダンゴ", "カギ",
                                          "ふさふさ", "ながまる", "透明"};
  Process::Read8(palicoChoice * 0x494 + 0x8338AC8, tail);
  Keyboard keyboard(
      "尻尾を選んでください。\n現在[" + listPalicoTail[tail] + "]",
      listPalicoTail);
  if (int choice = keyboard.Open() != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AC8, choice);
  }
}

void PalicoBodyHairColorRedChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("赤の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338ACC, a);
  }
}

void PalicoBodyHairColorGreenChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("緑の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338ACD, a);
  }
}

void PalicoBodyHairColorBlueChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("青の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338ACE, a);
  }
}

void PalicoRightEyeColorRedChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("赤の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD0, a);
  }
}

void PalicoRightEyeColorGreenChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("緑の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD1, a);
  }
}

void PalicoRightEyeColorBlueChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("青の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD2, a);
  }
}

void PalicoLeftEyeColorRedChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("赤の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD4, a);
  }
}

void PalicoLeftEyeColorGreenChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("緑の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD5, a);
  }
}

void PalicoLeftEyeColorBlueChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("青の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD6, a);
  }
}

void PalicoInnerColorRedChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("赤の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD8, a);
  }
}

void PalicoInnerColorGreenChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("緑の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338AD9, a);
  }
}

void PalicoInnerColorBlueChange(MenuEntry *entry) {
  u8 a;
  Keyboard keyboard("青の値を入力してください\n1~255の間");
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(a) != -1) {
    Process::Write8(palicoChoice * 0x494 + 0x8338ADA, a);
  }
}

void PalicoNameChange(MenuEntry *entry) {
  std::string nameFix, namenow, namekbd;
  Process::ReadString(0x83AE380, nameFix, 0x1E, StringFormat::Utf8);
  Process::ReadString(palicoChoice * 0x494 + 0x8338AFE, namenow, 0x1E,
                      StringFormat::Utf8);
  Keyboard keyboard("どちらで変更しますか？\n現在の名前[" + namenow + "]",
                    {"定型文", "キーボード"});
  int choice = keyboard.Open();
  if (choice == 0) {
    for (int i = 0; i < 8; i++) {
      Process::Write32(i * 4 + palicoChoice * 0x494 + 0x8338AFE, 0);
    }
    Process::WriteString(palicoChoice * 0x494 + 0x8338AFE, nameFix,
                         StringFormat::Utf8);
  }
  if (choice == 1) {
    Keyboard keyboard("名前を入力してください。");
    if (keyboard.Open(namekbd) != -1) {
      for (int i = 0; i < 8; i++) {
        Process::Write32(i * 4 + palicoChoice * 0x494 + 0x8338AFE, 0);
      }
      Process::WriteString(palicoChoice * 0x494 + 0x8338AFE, namekbd,
                           StringFormat::Utf8);
    }
  }
}

void PalicoCommentChange(MenuEntry *entry) {
  std::string nameFix, namenow, namekbd;
  Process::ReadString(0x83AE380, nameFix, 0x1E, StringFormat::Utf8);
  Process::ReadString(palicoChoice * 0x494 + 0x8338920, namenow, 0x1E,
                      StringFormat::Utf8);
  Keyboard keyboard("どちらで変更しますか？\n現在のコメント[" + namenow + "]",
                    {"定型文", "キーボード"});
  int choice = keyboard.Open();
  if (choice == 0) {
    for (int i = 0; i < 15; i++) {
      Process::Write32(i * 4 + palicoChoice * 0x494 + 0x8338920, 0);
    }
    Process::WriteString(palicoChoice * 0x494 + 0x8338920, nameFix,
                         StringFormat::Utf8);
  }
  if (choice == 1) {
    Keyboard keyboard("コメントを入力してください。");
    if (keyboard.Open(namekbd) != -1) {
      for (int i = 0; i < 15; i++) {
        Process::Write32(i * 4 + palicoChoice * 0x494 + 0x8338920, 0);
      }
      Process::WriteString(palicoChoice * 0x494 + 0x8338920, namekbd,
                           StringFormat::Utf8);
    }
  }
}

void PalicoGodParentChange(MenuEntry *entry) {
  std::string nameFix, namenow, namekbd;
  Process::ReadString(0x83AE380, nameFix, 0x1E, StringFormat::Utf8);
  Process::ReadString(palicoChoice * 0x494 + 0x833895C, namenow, 0x1E,
                      StringFormat::Utf8);
  Keyboard keyboard("どちらで変更しますか？\n現在の名付け親[" + namenow + "]",
                    {"定型文", "キーボード"});
  int choice = keyboard.Open();
  if (choice == 0) {
    for (int i = 0; i < 8; i++) {
      Process::Write32(i * 4 + palicoChoice * 0x494 + 0x833895C, 0);
    }
    Process::WriteString(palicoChoice * 0x494 + 0x833895C, nameFix,
                         StringFormat::Utf8);
  }
  if (choice == 1) {
    Keyboard keyboard("名付け親を入力してください。");
    if (keyboard.Open(namekbd) != -1) {
      for (int i = 0; i < 8; i++) {
        Process::Write32(i * 4 + palicoChoice * 0x494 + 0x833895C, 0);
      }
      Process::WriteString(palicoChoice * 0x494 + 0x833895C, namekbd,
                           StringFormat::Utf8);
    }
  }
}

void PalicoPredecessorHusbandChange(MenuEntry *entry) {
  std::string nameFix, namenow, namekbd;
  Process::ReadString(0x83AE380, nameFix, 0x1E, StringFormat::Utf8);
  Process::ReadString(palicoChoice * 0x494 + 0x833897C, namenow, 0x1E,
                      StringFormat::Utf8);
  Keyboard keyboard(
      "どちらで変更しますか？\n現在の先代旦那さん[" + namenow + "]",
      {"定型文", "キーボード"});
  int choice = keyboard.Open();
  if (choice == 0) {
    for (int i = 0; i < 8; i++) {
      Process::Write32(i * 4 + palicoChoice * 0x494 + 0x833897C, 0);
    }
    Process::WriteString(palicoChoice * 0x494 + 0x833897C, nameFix,
                         StringFormat::Utf8);
  }
  if (choice == 1) {
    Keyboard keyboard("先代旦那さんを入力してください。");
    if (keyboard.Open(namekbd) != -1) {
      for (int i = 0; i < 8; i++) {
        Process::Write32(i * 4 + palicoChoice * 0x494 + 0x833897C, 0);
      }
      Process::WriteString(palicoChoice * 0x494 + 0x833897C, namekbd,
                           StringFormat::Utf8);
    }
  }
}

void PalicoAbsorption(MenuEntry *entry) {
  u32 cat1Pointer, cat2Pointer, cat3Pointer, cat4Pointer;
  u32 player;
  float playerX, playerZ;
  Process::Read32(0x8327C04, cat1Pointer);
  Process::Read32(0x8327C08, cat2Pointer);
  Process::Read32(0x8327C0C, cat3Pointer);
  Process::Read32(0x8327C10, cat4Pointer);
  Process::Read32(0x8195350, player);
  Process::ReadFloat(player + 0x40, playerX);
  Process::ReadFloat(player + 0x48, playerZ);

  Process::WriteFloat(cat1Pointer + 0x40, playerX);
  Process::WriteFloat(cat1Pointer + 0x48, playerZ);
  Process::WriteFloat(cat2Pointer + 0x40, playerX);
  Process::WriteFloat(cat2Pointer + 0x48, playerZ);
  Process::WriteFloat(cat3Pointer + 0x40, playerX);
  Process::WriteFloat(cat3Pointer + 0x48, playerZ);
  Process::WriteFloat(cat4Pointer + 0x40, playerX);
  Process::WriteFloat(cat4Pointer + 0x48, playerZ);
}

void SpeedHack(MenuEntry *entry) {
  float speed;
  Process::ReadFloat(0x317298, speed);
  Keyboard keyboard(Utils::Format(
      "速度を何倍にしますか？\n-にすると後ろに移動します\n現在[%.2f]", speed));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(speed) != -1) {
    Process::WriteFloat(0x317298, speed);
  }
}

void ViewingAngleChangeV2(MenuEntry *entry) {
  float viewingAngle;
  Process::ReadFloat(0x9C4AD4, viewingAngle);
  Keyboard keyboard(Utils::Format(
      "視野を何倍に拡大しますか？\n-にすると上下反対になります。\n現在[%.2f]",
      viewingAngle));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(viewingAngle) != -1) {
    Process::WriteFloat(0x9C4AD4, viewingAngle);
  }
}

void WeaponSizeChange(MenuEntry *entry) {
  float size;
  Process::ReadFloat(0xA58AF0, size);
  Keyboard keyboard(
      Utils::Format("武器サイズを何倍にしますか？\n現在[%.2f]", size));
  keyboard.IsHexadecimal(false);
  if (keyboard.Open(size) != -1) {
    Process::WriteFloat(0xA58AF0, size);
  }
}

static u16 attackPoint;
static u16 defencePoint;
static u16 attributePoint;
static u16 resistanceFirePoint;
static u16 resistanceWaterPoint;
static u16 resistanceThunderPoint;
static u16 resistanceIcePoint;
static u16 resistanceDragonPoint;
void AttackPowerOption(MenuEntry *entry) {
  Keyboard keyboard("素の攻撃力を入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(attackPoint);
}

void AttackPowerChange(MenuEntry *entry) {
  Process::Write16(0x831B450, attackPoint);
}

void DefencePowerOption(MenuEntry *entry) {
  Keyboard keyboard("素の防御力を入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(defencePoint);
}

void DefencePowerChange(MenuEntry *entry) {
  Process::Write16(0x831B45E, defencePoint);
}

void AttributeOption(MenuEntry *entry) {
  Keyboard keyboard("素の属性値を入力してください。");
  keyboard.IsHexadecimal(false);
  keyboard.Open(attributePoint);
}

void AttributeChange(MenuEntry *entry) {
  Process::Write16(0x831B45A, attributePoint);
}

void ResistanceOption(MenuEntry *entry) {
  Keyboard keyboard("グループを選んでください。",
                    {"火耐性変更", "水耐性変更", "雷耐性変更", "氷耐性変更",
                     "龍耐性変更", "一括変更"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard("素の火耐性値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(resistanceFirePoint);
  }
  if (choice == 1) {
    Keyboard keyboard("素の水耐性値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(resistanceWaterPoint);
  }
  if (choice == 2) {
    Keyboard keyboard("素の雷耐性値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(resistanceThunderPoint);
  }
  if (choice == 3) {
    Keyboard keyboard("素の氷耐性値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(resistanceIcePoint);
  }
  if (choice == 4) {
    Keyboard keyboard("素の龍耐性値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(resistanceDragonPoint);
  }
  if (choice == 5) {
    u8 resistance;
    Keyboard keyboard("素の耐性値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(resistance);
    resistanceFirePoint = resistance;
    resistanceWaterPoint = resistance;
    resistanceThunderPoint = resistance;
    resistanceIcePoint = resistance;
    resistanceDragonPoint = resistance;
  }
}

void ResistanceChange(MenuEntry *entry) {
  Process::Write16(0x831B460, resistanceFirePoint);
  Process::Write16(0x831B462, resistanceWaterPoint);
  Process::Write16(0x831B464, resistanceThunderPoint);
  Process::Write16(0x831B466, resistanceIcePoint);
  Process::Write16(0x831B468, resistanceDragonPoint);
}

static u8 redInput, greenInput, blueInput;
void RedInput(MenuEntry *entry) {
  Keyboard keyboard("入力モードを選んでください。", {"10進数", "16進数"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard("R値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(redInput);
  }
  if (choice == 1) {
    Keyboard keyboard("R値を入力してください。");
    keyboard.Open(redInput);
  }
}

void GreenInput(MenuEntry *entry) {
  Keyboard keyboard("入力モードを選んでください。", {"10進数", "16進数"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard("G値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(greenInput);
  }
  if (choice == 1) {
    Keyboard keyboard("G値を入力してください。");
    keyboard.Open(greenInput);
  }
}

void BlueInput(MenuEntry *entry) {
  Keyboard keyboard("入力モードを選んでください。", {"10進数", "16進数"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard("B値を入力してください。");
    keyboard.IsHexadecimal(false);
    keyboard.Open(blueInput);
  }
  if (choice == 1) {
    Keyboard keyboard("B値を入力してください。");
    keyboard.Open(blueInput);
  }
}

void RGBOutput(MenuEntry *entry) {
  Keyboard keyboard("グループを選んでください。",
                    {"入力された値を確認", "出力された色を確認"});
  int choice = keyboard.Open();
  if (choice == 0) {
    MessageBox(Utils::Format("入力された値です。\nR[%02X]\nG[%02X]\nB[%02X]",
                             redInput, greenInput, blueInput))();
  }
  if (choice == 1) {
    MessageBox("出力された色です。\n"
                   << Color(redInput, greenInput, blueInput)
                   << "■■■■■■■■■\n■■■■■■■■■\n■■■■■■■■■")();
  }
}

void HexEditor(MenuEntry *entry) {
  static int addressOn = 0;
  static u32 Hex, Hex1, Hex2, Hex3, Hex4, Hex5, Hex6, Hex7, Hex8, Hex9, Hex11;
  static u32 address, address1 = 0x00100000, address2, address3, address4,
      address5;
  static u32 aiu, aiu1;
  static int Hex10 = 0;
  if (entry->Hotkeys[0].IsDown()) {
    Keyboard keyboard("アドレスを入力してください。");
    keyboard.IsHexadecimal(false);
    if (keyboard.Open(address1, address1) != -1) {
      aiu = address1 / 4;
      if (aiu % 2 == 0) {
        Hex10 = 0;
        address1 = 4 * aiu;
      } else {
        Hex10 = 1;
        aiu1 = aiu - 1;
        address1 = 4 * aiu1;
      }
      return;
    }
  }
  if (entry->Hotkeys[1].IsDown()) {
    Keyboard keyboard("値を入力してください。");
    if (keyboard.Open(Hex11, Hex11) != -1) {
      Process::Write32(address, Hex11);
      return;
    }
  }
  if (Controller::IsKeysPressed(A + DPadLeft) && Hex10 == 0) {
    Hex10 = 1;
  }
  if (Controller::IsKeysPressed(A + DPadRight) && Hex10 == 0) {
    Hex10 = 1;
  }
  if (Controller::IsKeysPressed(A + DPadLeft) && Hex10 == 1) {
    Hex10 = 0;
  }
  if (Controller::IsKeysPressed(A + DPadRight) && Hex10 == 1) {
    Hex10 = 0;
  }
  if (Controller::IsKeysPressed(A + DPadUp)) {
    address1 -= 8;
  }
  if (Controller::IsKeysPressed(A + DPadDown)) {
    address1 += 8;
  }
  address = address1 + (Hex10 * 4);
  address2 = address1 + 8;
  address3 = address1 + 16;
  address4 = address1 + 24;
  address5 = address1 + 32;
  Process::Read32(address1, Hex);
  Process::Read32(address1 + 4, Hex1);
  Process::Read32(address1 + 8, Hex2);
  Process::Read32(address1 + 12, Hex3);
  Process::Read32(address1 + 16, Hex4);
  Process::Read32(address1 + 20, Hex5);
  Process::Read32(address1 + 24, Hex6);
  Process::Read32(address1 + 28, Hex7);
  Process::Read32(address1 + 32, Hex8);
  Process::Read32(address1 + 36, Hex9);
  Process::Read32(address, Hex11);
  addressOn = true;
  OSD::Run([](const Screen &screen) {
    if (!screen.IsTop) {
      return (false);
    }
    if (addressOn == true) {
      screen.Draw(Utils::Format("%08X  03020100 07060504", address), 0, 0);
      screen.Draw(Utils::Format("%08X  ", address1), 0, 10);
      if (Hex10 == 0) {
        screen.Draw(Utils::Format("%08X ", Hex), 60, 10, Color::Yellow);
        screen.Draw(Utils::Format("%08X", Hex1), 114, 10);
      }
      if (Hex10 == 1) {
        screen.Draw(Utils::Format("%08X ", Hex), 60, 10);
        screen.Draw(Utils::Format("%08X", Hex1), 114, 10, Color::Yellow);
      }
      screen.Draw(Utils::Format("%08X  %08X %08X", address2, Hex2, Hex3), 0,
                  20);
      screen.Draw(Utils::Format("%08X  %08X %08X", address3, Hex4, Hex5), 0,
                  30);
      screen.Draw(Utils::Format("%08X  %08X %08X", address4, Hex6, Hex7), 0,
                  40);
      screen.Draw(Utils::Format("%08X  %08X %08X", address5, Hex8, Hex9), 0,
                  50);
      addressOn = false;
    }
    return (true);
  });
}

void HexEditor2(MenuEntry *entry) {
  static float float1;
  static u32 hex1, hex2, hex3, hex4;
  static u32 ad1 = 0x00100000, ad2, ad3, ad4;
  static int addressOn = 0;
  if (entry->Hotkeys[0].IsDown()) {
    Keyboard keyboard("アドレスを入力してください。");
    keyboard.Open(ad1, ad1);
  }
  if (entry->Hotkeys[1].IsDown()) {
    Keyboard keyboard("値を入力してください。");
    if (keyboard.Open(hex1, hex1) != -1) {
      Process::Write32(ad1, hex1);
    }
  }
  if (Controller::IsKeysPressed(A + DPadUp)) {
    ad1 -= 4;
  }
  if (Controller::IsKeysPressed(A + DPadDown)) {
    ad1 += 4;
  }
  ad1 = ad1 + 0x0;
  ad2 = ad1 + 0x4;
  ad3 = ad1 + 0x8;
  ad4 = ad1 + 0xC;
  Process::Read32(ad1, hex1);
  Process::Read32(ad2, hex2);
  Process::Read32(ad3, hex3);
  Process::Read32(ad4, hex4);
  addressOn = true;
  OSD::Run([](const Screen &screen) {
    if (!screen.IsTop) {
      return (false);
    }
    if (addressOn == true) {
      screen.Draw(Utils::Format("%08X  03020100", ad1), 0, 0);
      screen.Draw(Utils::Format("%08X  ", ad1), 0, 10);
      screen.Draw(Utils::Format("%08X", hex1), 60, 10, Color::Yellow);
      screen.Draw(Utils::Format("%08X  %08X", ad2, hex2), 0, 20);
      screen.Draw(Utils::Format("%08X  %08X", ad3, hex3), 0, 30);
      screen.Draw(Utils::Format("%08X  %08X", ad4, hex4), 0, 40);
      addressOn = false;
    }
    return (true);
  });
}

void MySetToPorchItemCopy(MenuEntry *entry) {
  u32 item;
  std::string mySet1, mySet2, mySet3, mySet4;
  std::string mySet5, mySet6, mySet7, mySet8;
  Process::ReadString(0x8376190, mySet1, 30, StringFormat::Utf8);
  Process::ReadString(0x837623A, mySet2, 30, StringFormat::Utf8);
  Process::ReadString(0x83762E4, mySet3, 30, StringFormat::Utf8);
  Process::ReadString(0x837638E, mySet4, 30, StringFormat::Utf8);
  Process::ReadString(0x8376438, mySet5, 30, StringFormat::Utf8);
  Process::ReadString(0x83764E2, mySet6, 30, StringFormat::Utf8);
  Process::ReadString(0x837658C, mySet7, 30, StringFormat::Utf8);
  Process::ReadString(0x8376636, mySet8, 30, StringFormat::Utf8);
  Keyboard keyboard(
      "アイテムポーチにコピーしたいアイテムマイセットを選んでください。\n"
      "名前の表示がおかしいのは仕様です。",
      {mySet1, mySet2, mySet3, mySet4, mySet5, mySet6, mySet7, mySet8});
  if (int choice = keyboard.Open() != -1) {
    for (int i = 0; i < 32; i++) {
      Process::Read32(i * 4 + choice * 0xAA + 0x83761BA, item);
      Process::Write32(i * 4 + choice * 0xAA + 0x8372392, item);
    }
  }
}

void DeliveryItemToPorchCopy(MenuEntry *entry) {
  u16 item1, item2;
  u16 quantity1, quantity2;
  u16 itemRead1, itemRead2;
  Process::Read16(0x8363F98, item1);
  Process::Read16(0x8363F9C, quantity1);
  Process::Read16(0x8363FB0, item2);
  Process::Read16(0x8363FB4, quantity2);
  Process::Read16(0x8372392, itemRead1);
  Process::Read16(0x8372396, itemRead2);
  Keyboard keyboard("納品アイテムをアイテムポーチにコピーしますか？",
                    listToggle);
  int choice = keyboard.Open();
  if (choice == 0) {
    if (itemRead1 != 0 && itemRead2 != 0) {
      if (MessageBox("ポーチの1番目と2番目に空きがありません。\n"
                     "コピーしますか？",
                     DialogType::DialogYesNo)()) {
        Process::Write16(0x8372392, item1);
        Process::Write16(0x8372394, quantity1);
        Process::Write16(0x8372396, item2);
        Process::Write16(0x8372398, quantity2);
      }
    } else {
      Process::Write16(0x8372392, item1);
      Process::Write16(0x8372394, quantity1);
      Process::Write16(0x8372396, item2);
      Process::Write16(0x8372398, quantity2);
    }
  }
}

void PorchToDeliveryItemCopy(MenuEntry *entry) {
  u16 itemRead1, itemRead2;
  u16 quantity1, quantity2;
  Process::Read16(0x8372392, itemRead1);
  Process::Read16(0x8372394, quantity1);
  Process::Read16(0x8372396, itemRead2);
  Process::Read16(0x8372398, quantity2);
  Keyboard keyboard("アイテムポーチのアイテムを納品アイテムにコピーしますか？",
                    listToggle);
  int choice = keyboard.Open();
  if (choice == 0) {
    Process::Write16(0x8363F98, itemRead1);
    Process::Write16(0x8363F98, quantity1);
    Process::Write16(0x8363F98, itemRead2);
    Process::Write16(0x8363F98, quantity2);
  }
}

void IfRunMoonWalk(MenuEntry *entry) {
  Keyboard keyboard("走った時にムーンウォークをしますか？", listToggle);
  int choice = keyboard.Open();
  if (choice == 0) {
    Process::Write32(0x3173C8, 0xE3A00001);
  }
  if (choice == 1) {
    Process::Write32(0x3173C8, 0xE3A00000);
  }
}

void InQuestSpeedHack(MenuEntry *entry) {
  float questTrue, questFalse;
  Keyboard keyboard("グループを選んでください。",
                    {"クエスト中武器適応", "クエスト中武器無適応"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard("クエスト中の移動速度(武器適応)を入力してください。");
    if (keyboard.Open(questTrue) != -1) {
      Process::WriteFloat(0x3250C8, questTrue);
    }
  }
  if (choice == 1) {
    Keyboard keyboard("クエスト中の移動速度(武器無適応)を入力してください。");
    if (keyboard.Open(questFalse) != -1) {
      Process::WriteFloat(0x338D40, questFalse);
    }
  }
}

static float hunterSizeX = 1, hunterSizeY = 1, hunterSizeZ = 1;
void HunterSizeOption(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8195350, offset);
  Process::ReadFloat(offset + 0x60, hunterSizeX);
  Process::ReadFloat(offset + 0x64, hunterSizeY);
  Process::ReadFloat(offset + 0x68, hunterSizeZ);
  Keyboard keyboard("グループを選んでください。",
                    {"X倍率", "Y倍率", "Z倍率", "一括変更"});
  int choice = keyboard.Open();
  if (choice == 0) {
    Keyboard keyboard(
        Utils::Format("X倍率を入力してください。\n現在X[%f]", hunterSizeX));
    keyboard.Open(hunterSizeX);
  }
  if (choice == 1) {
    Keyboard keyboard(
        Utils::Format("Y倍率を入力してください。\n現在Y[%f]", hunterSizeY));
    keyboard.Open(hunterSizeY);
  }
  if (choice == 2) {
    Keyboard keyboard(
        Utils::Format("Z倍率を入力してください。\n現在Z[%f]", hunterSizeZ));
    keyboard.Open(hunterSizeZ);
  }
  if (choice == 3) {
    Keyboard keyboard(
        Utils::Format("倍率を入力してください。\n現在\nX[%f]\nY[%f]\nZ[%f]",
                      hunterSizeX, hunterSizeY, hunterSizeZ));
    if (keyboard.Open(hunterSizeX) != -1) {
      hunterSizeY = hunterSizeX;
      hunterSizeZ = hunterSizeX;
    }
  }
}

void HunterSizeChange(MenuEntry *entry) {
  u32 offset;
  Process::Read32(0x8195350, offset);
  Process::WriteFloat(offset + 0x60, hunterSizeX);
  Process::WriteFloat(offset + 0x64, hunterSizeY);
  Process::WriteFloat(offset + 0x68, hunterSizeZ);
}

void MaximumFpsChange(MenuEntry *entry) {
  float fps;
  Keyboard key("最大FPSを入力してください。");
  key.Open(fps);
  Process::WriteFloat(0x87E24E0, fps);
}

void MealInfinite(MenuEntry *entry) { Process::Write8(0x8480827, 0); }

void LuxuryCouponGrant(MenuEntry *entry) {
  Process::Write8(0x8480825, 2);
  Process::Write8(0x8480826, 2);
}

void MeetRequestInfinite(MenuEntry *entry) { Process::Write8(0x8480925, 0); }

void MealHpUp(MenuEntry *entry) { Process::Write8(0x83A6E68, 127); }

void MealStaminaUp(MenuEntry *entry) { Process::Write8(0x83A6E69, 127); }

void MealAttackPowerUp(MenuEntry *entry) { Process::Write8(0x83A6E6A, 127); }

void MealDefencePowerUp(MenuEntry *entry) { Process::Write8(0x83A6E6B, 127); }

void MealFireResistanceUp(MenuEntry *entry) { Process::Write8(0x83A6E6C, 127); }

void MealWaterResistanceUp(MenuEntry *entry) {
  Process::Write8(0x83A6E6D, 127);
}

void MealThunderResistanceUp(MenuEntry *entry) {
  Process::Write8(0x83A6E6E, 127);
}

void MealIceResistanceUp(MenuEntry *entry) { Process::Write8(0x83A6E6F, 127); }

void MealDragonResistanceUp(MenuEntry *entry) {
  Process::Write8(0x83A6E70, 127);
}

void MealSkillChange(MenuEntry *entry) {
  std::vector<std::string> listMealSkill{"なし",
                                         "ネコの解体術【大】",
                                         "ネコの解体術【小】",
                                         "ネコの医療術",
                                         "ネコの体術",
                                         "ネコの火薬術",
                                         "ネコの特殊攻撃術",
                                         "ネコの防御術【大】",
                                         "ネコの防御術【小】",
                                         "ネコの吹奏術",
                                         "ネコの道具倹約術",
                                         "ネコのカリスマ",
                                         "ネコの調合術【大】",
                                         "ネコの調合術【小】",
                                         "ネコの採取術",
                                         "ネコの射撃術",
                                         "招きネコの激運",
                                         "招きネコの幸運",
                                         "ネコの火事場力",
                                         "ネコのはじかれ上手",
                                         "ネコの逃走術",
                                         "ネコの投擲術",
                                         "ネコの胆力",
                                         "ネコの運搬の超人",
                                         "ネコの運搬の鉄人",
                                         "ネコの弱いの来い！",
                                         "ネコの秘境探索術",
                                         "ネコの換算術",
                                         "ネコの起き上り術【大】",
                                         "ネコの起き上り術【小】",
                                         "ネコの暴れ撃ち",
                                         "ネコの蹴脚術",
                                         "ネコの拳闘術",
                                         "ネコのはりつき超人",
                                         "ネコのはりつき鉄人",
                                         "ネコの解体の鉄人",
                                         "ネコの着地術",
                                         "ネコの休憩術",
                                         "ネコのゴリ押し術",
                                         "ネコのおまけ術",
                                         "ネコのKO術",
                                         "招きネコの金運",
                                         "ネコの砲撃術",
                                         "ネコのド根性",
                                         "ネコのこやし玉達人",
                                         "ネコの毛づくろい上手",
                                         "ネコの長靴術",
                                         "ネコのすり抜け術",
                                         "ネコの千里眼の術",
                                         "ネコの研磨術",
                                         "ネコの受け身術",
                                         "ネコのかかってこい",
                                         "ネコのオトモ指導術",
                                         "ネコの短期催眠術",
                                         "ネコの手配上手",
                                         "ネコの不眠術",
                                         "ネコのふんばり術",
                                         "ネコの釣り上手",
                                         "招きネコの悪運",
                                         "ネコの乗り上手",
                                         "ネコの乗り支援術",
                                         "ネコの報酬金保険",
                                         "ネコの憎まれ上手"};

  Keyboard keyboard("どちらのスキルを変更しますか？",
                    {"第一スキル", "第二スキル", "第三スキル"});
  int select = keyboard.Open();
  if (select != -1) {
    Keyboard key("スキルを選択してください。", listMealSkill);
    int choice = key.Open();
    if (choice != -1) {
      Process::Write8(0x83A6E71 + select, choice);
    }
  }
}

void Teleport(MenuEntry *entry) {
  u32 offset;
  float x, y, z;
  Process::Read32(0x8195350, offset);

  if (Controller::IsKeysDown(X + DPadRight)) {
    Process::ReadFloat(offset + 0x40, x);
    Process::ReadFloat(offset + 0x44, y);
    Process::ReadFloat(offset + 0x48, z);
  }

  if (Controller::IsKeysDown(X + DPadLeft)) {
    Process::WriteFloat(offset + 0x40, x);
    Process::WriteFloat(offset + 0x44, y);
    Process::WriteFloat(offset + 0x48, z);
  }
}

void LocalTimeDisplay(MenuEntry *entry) {
  std::time_t time = std::time(nullptr);
  static std::tm calendar_time = *std::localtime(std::addressof(time));
  const int kStartYear = 1900;
  const int kStartMonth = 1;
  static int time_hour;
  static std::string am_or_pm;
  const std::vector<std::string> kListTimeOfTheWeek{
      "日", "月", "火", "水", "木", "金", "土",
  };
  static std::string time_of_the_week =
      kListTimeOfTheWeek[calendar_time.tm_wday];

  if (calendar_time.tm_hour % 12 == 0) {
    time_hour = 12;
  } else {
    time_hour = calendar_time.tm_hour % 12;
  }

  if (calendar_time.tm_hour / 12) {
    am_or_pm = "午後";
  } else {
    am_or_pm = "午前";
  }

  MessageBox(Utils::Format(
      "%d年:%2d月:%2d日:%s曜日:%s%2d時:%2d分:%2d秒",
      calendar_time.tm_year + kStartYear, calendar_time.tm_mon + kStartMonth,
      calendar_time.tm_mday, time_of_the_week.c_str(), am_or_pm.c_str(),
      time_hour, calendar_time.tm_min, calendar_time.tm_sec))();
}

}  // namespace CTRPluginFramework