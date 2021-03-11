#pragma once
#include <string>
#include <vector>
#include <ctime>

#include <3ds.h>
#include <CTRPluginFramework.hpp>
#include "csvc.h"
#include "Patch.hpp"
#include "Keyboard.hpp"
#include "TeamAndConditions.hpp"

#define KEY_DU DPadUp
#define KEY_DD DPadDown
#define KEY_DL DPadLeft
#define KEY_DR DPadRight
#define KEY_CU CPadUp
#define KEY_CD CPadDown
#define KEY_CL CPadLeft
#define KEY_CR CPadRight

namespace CTRPluginFramework
{
    using CallbackPointer = void (*)(void);
    using StringVector = std::vector<std::string>;

    // プレイヤー
    // ステータス変更
    void AttackPowerChange(MenuEntry* entry);
    void AttackPowerOption(MenuEntry* entry);
    void DefencePowerChange(MenuEntry* entry);
    void DefencePowerOption(MenuEntry* entry);
    void AttributeChange(MenuEntry* entry);
    void AttributeOption(MenuEntry* entry);
    void ResistanceChange(MenuEntry* entry);
    void ResistanceOption(MenuEntry* entry);
    // ステータス変更終わり

    // プレイヤー情報変更
    // 狩技変更
    void HunterArt1Change(MenuEntry* entry);
    void HunterArt2Change(MenuEntry* entry);
    void HunterArt3Change(MenuEntry* entry);
    // 狩技変更終わり

    // 肌の色変更
    void SkinRedChange(MenuEntry* entry);
    void SkinGreenChange(MenuEntry* entry);
    void SkinBlueChange(MenuEntry* entry);
    void SkinColorChange(MenuEntry* entry);
    // 肌の色変更終わり

    // 食事
    // フラグ
    void MealInfinite(MenuEntry* entry);
    void LuxuryCouponGrant(MenuEntry* entry);
    void MeetRequestInfinite(MenuEntry* entry);
    // フラグ終わり

    // ステータス
    // 耐性
    void MealFireResistanceUp(MenuEntry* entry);
    void MealWaterResistanceUp(MenuEntry* entry);
    void MealThunderResistanceUp(MenuEntry* entry);
    void MealIceResistanceUp(MenuEntry* entry);
    void MealDragonResistanceUp(MenuEntry* entry);
    // 耐性終わり

    void MealHpUp(MenuEntry* entry);
    void MealStaminaUp(MenuEntry* entry);
    void MealAttackPowerUp(MenuEntry* entry);
    void MealDefencePowerUp(MenuEntry* entry);
    // ステータス終わり

    void MealSkillChange(MenuEntry* entry);
    // 食事終わり

    void PlayerVoiceChange(MenuEntry* entry);
    void PlayerEyeColorChange(MenuEntry* entry);
    void PlayerInnerChange(MenuEntry* entry);
    void PlayerGenderChange(MenuEntry* entry);
    void PlayerHuntingStyleChange(MenuEntry* entry);
    void PlayerHearStyleChange(MenuEntry* entry);
    void PlayerFaceChange(MenuEntry* entry);
    void PlayerMakeChange(MenuEntry* entry);
    // プレイヤー情報変更終わり

    void PlayerAttackPowerMagnificationChange(MenuEntry* entry);
    void PlayerAttackPowerMagnificationOption(MenuEntry* entry);
    void playerDefencePowerMagnificationChange(MenuEntry* entry);
    void PlayerDefencePowerMagnificationOption(MenuEntry* entry);
    void PlayerSpeedChange(MenuEntry* entry);
    void PlayerSpeedOption(MenuEntry* entry);
    void PlayerCoordinateModifier(MenuEntry* entry);
    void PlayerMoonJump(MenuEntry* entry);
    void Teleport(MenuEntry* entry);
    void Stalker(MenuEntry* entry);
    void Repeatmove(MenuEntry* entry);
    void HunterArtRelease(MenuEntry* entry);
    void HungryInvalid(MenuEntry* entry);
    void HunterSizeChange(MenuEntry* entry);
    void HunterSizeOption(MenuEntry* entry);
    void InfiniteHP(MenuEntry* entry);
    void Invincible(MenuEntry* entry);
    void SuperArmor(MenuEntry* entry);
    void InfiniteStamina(MenuEntry* entry);
    void InfiniteHunterArt(MenuEntry* entry);
    void Always3HunterArtEquip(MenuEntry* entry);
    void AlwaysDisplayMap(MenuEntry* entry);
    void AlwaysPaint(MenuEntry* entry);
    void SpeedHack(MenuEntry* entry);
    void InQuestSpeedHack(MenuEntry* entry);
    void IfRunMoonWalk(MenuEntry* entry);
    void HunterNameChange(MenuEntry* entry);
    // プレイヤー終わり

    // アイテム
    // 装備
    // 護石編集
    void AmuletCreate(MenuEntry* entry);
    void AmuletTypeChange(MenuEntry* entry);
    void AmuletSkillChange(MenuEntry* entry);
    void AmuletSkillPointChange(MenuEntry* entry);
    void AmuletSlotChange(MenuEntry* entry);
    // 護石編集終わり

    // 猟虫編集
    void InsectTypeChange(MenuEntry* entry);
    void InsectLevelChange(MenuEntry* entry);
    void InsectPowerChange(MenuEntry* entry);
    void InsectWeightChange(MenuEntry* entry);
    void InsectStaminaChange(MenuEntry* entry);
    void InsectFireAttributeChange(MenuEntry* entry);
    void InsectWaterAttributeChange(MenuEntry* entry);
    void InsectThunderAttributeChange(MenuEntry* entry);
    void InsectIceAttributeChange(MenuEntry* entry);
    void InsectDragonAttributeChange(MenuEntry* entry);
    // 猟虫編集終わり

    void OtherPlayerEquipmentCopy(MenuEntry* entry);
    // 装備終わり

    void InfiniteBombPut(MenuEntry* entry);
    void TanhoreItemSet(MenuEntry* entry);
    void MoneyChange(MenuEntry* entry);
    void WycademyPointChange(MenuEntry* entry);
    void InfiniteItemAmmo(MenuEntry* entry);
    void NoMaterialCompound(MenuEntry* entry);
    void CargoPutInPorch(MenuEntry* entry);
    void InfiniteCollect(MenuEntry* entry);
    void NoMaterialEquipmentCreate(MenuEntry* entry);
    void EquipmentAllRelease(MenuEntry* entry);
    void AllItemSold(MenuEntry* entry);
    void ItemBox1400Expansion(MenuEntry* entry);
    void HaveItem99(MenuEntry* entry);
    void ItemBoxEdit(MenuEntry* entry);
    void MySetToPorchItemCopy(MenuEntry* entry);
    void DeliveryItemToPorchCopy(MenuEntry* entry);
    void PorchToDeliveryItemCopy(MenuEntry* entry);
    void PorchAllClear(MenuEntry* entry);
    void SpecialPermitQuestTicketChange(MenuEntry* entry);
    // アイテム終わり

    // 武器
    // 武器別チート
    // ガンランスチート
    void GunlanceHeatGageFix(MenuEntry* entry);
    void GunlanceHeatGageOption(MenuEntry* entry);
    void GunlanceAmmoInfinite(MenuEntry* entry);
    void GunlanceInvalidOverHeat(MenuEntry* entry);
    // ガンランスチート終わり

    // 操虫棍チート
    void InsectGlaiveAlwaysTripleUp(MenuEntry* entry);
    void InsectGlaiveInsectStaminaInfinite(MenuEntry* entry);
    // 操虫棍チート終わり

    // ボウガンチート
    void BowgunAmmoInfinite(MenuEntry* entry);
    void BowgunCrouchingShot(MenuEntry* entry);
    // ボウガンチート終わり

    void ChargeStageFix(MenuEntry* entry);
    void ChageStageOption(MenuEntry* entry);
    void WeaponGageFix(MenuEntry* entry);
    void ChargeAxeBinFix(MenuEntry* entry);
    void HuntingHornAllEffectGrant(MenuEntry* entry);
    // 武器別チート終わり

    void AttributePointChange(MenuEntry* entry);
    void NoMotion(MenuEntry* entry);
    void CriticalRate100(MenuEntry* entry);
    void BowgunAutoReload(MenuEntry* entry);
    void InfiniteSharpness(MenuEntry* entry);
    void SharpnessPlus2(MenuEntry* entry);
    void ChargeSpeedUp(MenuEntry* entry);
    void ChargeGageMax(MenuEntry* entry);
    // 武器終わり

    // モンスター
    // モンスター情報画面表示
    void Monster1HpDisplay(MenuEntry* entry);
    void Monster2HpDisplay(MenuEntry* entry);
    void Monster1SizeMagnificationDisplay(MenuEntry* entry);
    void Monster2SizeMagnificationDisplay(MenuEntry* entry);
    // モンスター情報画面表示終わり

    void RideGageMax(MenuEntry* entry);
    void MonsterCoordinateModifier(MenuEntry* entry);
    void MonsterStalker(MenuEntry* entry);
    void MonsterActionRepeat(MenuEntry* entry);
    void MonsterActionRepeatOption(MenuEntry* entry);
    void Monster1And2Stop(MenuEntry* entry);
    void Monster1SizeChange(MenuEntry* entry);
    void Monster1SizeOption(MenuEntry* entry);
    void Monster2SizeChange(MenuEntry* entry);
    void Monster2SizeOption(MenuEntry* entry);
    void Monster1SpeedAttributeChange(MenuEntry* entry);
    void Monster1SpeedAttributeOption(MenuEntry* entry);
    void Monster2SpeedAttributeChange(MenuEntry* entry);
    void Monster2SpeedAttributeOption(MenuEntry* entry);
    void Monster1And2AlwaysPoison(MenuEntry* entry);
    void Monster1And2AlwaysParalysis(MenuEntry* entry);
    void Monster1And2AlwaysSleep(MenuEntry* entry);
    void Monster1And2AlwaysInvisible(MenuEntry* entry);
    void OneAttackKill(MenuEntry* entry);
    // モンスター終わり

    // ねこ
    // ねこ編集
    void PalicoChoice(MenuEntry* entry);

    // 装備サポート行動
    void PalicoEquipmentSupportAction1Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction2Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction3Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction4Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction5Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction6Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction7Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction8Change(MenuEntry* entry);
    // 装備サポート行動終わり

    // 装備オトモスキル
    void PalicoEquipmentSkill1Change(MenuEntry* entry);
    void PalicoEquipmentSkill2Change(MenuEntry* entry);
    void PalicoEquipmentSkill3Change(MenuEntry* entry);
    void PalicoEquipmentSkill4Change(MenuEntry* entry);
    void PalicoEquipmentSkill5Change(MenuEntry* entry);
    void PalicoEquipmentSkill6Change(MenuEntry* entry);
    void PalicoEquipmentSkill7Change(MenuEntry* entry);
    void PalicoEquipmentSkill8Change(MenuEntry* entry);
    // 装備オトモスキル終わり

    // 習得サポート行動
    void PalicoLearnSupportAction1Change(MenuEntry* entry);
    void PalicoLearnSupportAction2Change(MenuEntry* entry);
    void PalicoLearnSupportAction3Change(MenuEntry* entry);
    void PalicoLearnSupportAction4Change(MenuEntry* entry);
    void PalicoLearnSupportAction5Change(MenuEntry* entry);
    void PalicoLearnSupportAction6Change(MenuEntry* entry);
    void PalicoLearnSupportAction7Change(MenuEntry* entry);
    void PalicoLearnSupportAction8Change(MenuEntry* entry);
    void PalicoLearnSupportAction9Change(MenuEntry* entry);
    void PalicoLearnSupportAction10Change(MenuEntry* entry);
    void PalicoLearnSupportAction11Change(MenuEntry* entry);
    void PalicoLearnSupportAction12Change(MenuEntry* entry);
    void PalicoLearnSupportAction13Change(MenuEntry* entry);
    void PalicoLearnSupportAction14Change(MenuEntry* entry);
    void PalicoLearnSupportAction15Change(MenuEntry* entry);
    void PalicoLearnSupportAction16Change(MenuEntry* entry);
    // 習得サポート行動終わり

    // 習得オトモスキル
    void PalicoLearnSupportSkill1Change(MenuEntry* entry);
    void PalicoLearnSupportSkill2Change(MenuEntry* entry);
    void PalicoLearnSupportSkill3Change(MenuEntry* entry);
    void PalicoLearnSupportSkill4Change(MenuEntry* entry);
    void PalicoLearnSupportSkill5Change(MenuEntry* entry);
    void PalicoLearnSupportSkill6Change(MenuEntry* entry);
    void PalicoLearnSupportSkill7Change(MenuEntry* entry);
    void PalicoLearnSupportSkill8Change(MenuEntry* entry);
    void PalicoLearnSupportSkill9Change(MenuEntry* entry);
    void PalicoLearnSupportSkill10Change(MenuEntry* entry);
    void PalicoLearnSupportSkill11Change(MenuEntry* entry);
    void PalicoLearnSupportSkill12Change(MenuEntry* entry);
    // 習得オトモスキル終わり

    // 見た目
    // 見た目の色変更
    // 毛色
    void PalicoBodyHairColorRedChange(MenuEntry* entry);
    void PalicoBodyHairColorGreenChange(MenuEntry* entry);
    void PalicoBodyHairColorBlueChange(MenuEntry* entry);
    // 毛色終わり

    // 右目の色
    void PalicoRightEyeColorRedChange(MenuEntry* entry);
    void PalicoRightEyeColorGreenChange(MenuEntry* entry);
    void PalicoRightEyeColorBlueChange(MenuEntry* entry);
    // 右目の色終わり

    // 左目の色
    void PalicoLeftEyeColorRedChange(MenuEntry* entry);
    void PalicoLeftEyeColorGreenChange(MenuEntry* entry);
    void PalicoLeftEyeColorBlueChange(MenuEntry* entry);
    // 左目の色終わり

    // インナーの色
    void PalicoInnerColorRedChange(MenuEntry* entry);
    void PalicoInnerColorGreenChange(MenuEntry* entry);
    void PalicoInnerColorBlueChange(MenuEntry* entry);
    // インナーの色終わり

    // 見た目の色変更終わり

    void PalicoVoiceChange(MenuEntry* entry);
    void PalicoEyeChange(MenuEntry* entry);
    void PalicoInnerChange(MenuEntry* entry);
    void PalicoFurCoatChange(MenuEntry* entry);
    void PalicoEarChange(MenuEntry* entry);
    void PalicoTailChange(MenuEntry* entry);
    // 見た目終わり

    void PalicoExperienceChange(MenuEntry* entry);
    void PalicoLevelChange(MenuEntry* entry);
    void PalicoSupportTrendChange(MenuEntry* entry);
    void PalicoClosenessChange(MenuEntry* entry);
    void PalicoTargetChange(MenuEntry* entry);
    void PalicoCommentEditPossibleChange(MenuEntry* entry);
    void SpecialDeliveryDisplayChange(MenuEntry* entry);
    void PalicoNameChange(MenuEntry* entry);
    void PalicoCommentChange(MenuEntry* entry);
    void PalicoGodParentChange(MenuEntry* entry);
    void PalicoPredecessorHusbandChange(MenuEntry* entry);
    // ねこ編集終わり

    void PalicoAttackPowerMagnificationChange(MenuEntry* entry);
    void PalicoAttackPowerMagnificationOption(MenuEntry* entry);
    void PalicoDefencePowerMagnificationChange(MenuEntry* entry);
    void PalicoDefencePowerMagnificationOption(MenuEntry* entry);
    void PalicoAbsorption(MenuEntry* entry);
    void ProwlerSupportGageMax(MenuEntry* entry);
    // ねこ終わり

    // その他
    // チャット
    void ChatInfinite(MenuEntry* entry);
    void ChatConversionChange(MenuEntry* entry);
    void ChatConversionList(MenuEntry* entry);
    // チャット終わり

    // 酔っぱらい
    void InstantDrunk(MenuEntry* entry);
    void InstantDrunkOption(MenuEntry* entry);
    void Drunk1(MenuEntry* entry);
    // 酔っぱらい終わり

    // ハンターランク
    void HunterRankChange(MenuEntry* entry);
    void HunterRankPointChange(MenuEntry* entry);
    // ハンターランク終わり

    // プーギー＆フェニー
    void FenyAndPugyClothes(MenuEntry* entry);
    void FenyAndPugyNameChange(MenuEntry* entry);
    // プーギー＆フェニー終わり

    // クエスト
    void QuestClear(MenuEntry* entry);
    void QuestClearOption(MenuEntry* entry);
    void QuestWaitSkip(MenuEntry* entry);
    void QuestResultSkip(MenuEntry* entry);
    void QuestDownMaxChange(MenuEntry* entry);
    void QuestDownMaxOption(MenuEntry* entry);
    void QuestDownNowChange(MenuEntry* entry);
    void QuestDownNowOption(MenuEntry* entry);
    void QuestTimeDisplay(MenuEntry* entry);
    void SaveScreenFix(MenuEntry* entry);
    void SaveScreenOption(MenuEntry* entry);
    void QuestTimeStop(MenuEntry* entry);
    void AllQuestClearChange(MenuEntry* entry);
    // クエスト終わり

    // 集会所
    // 集会所を作る
    void BaseCreateTargetChange(MenuEntry* entry);
    void BaseCreateQuestTypeChange(MenuEntry* entry);
    void BaseCreateRecruitmentHunterRankMinimumChange(MenuEntry* entry);
    void BaseCreateRecruitmentHunterRankMaximumChange(MenuEntry* entry);
    void BaseCreateEntryPeopleChange(MenuEntry* entry);
    void BaseCreateEntryLimitChange(MenuEntry* entry);
    void BaseCreatePasswordExistChange(MenuEntry* entry);
    void BaseCreateRecruitmentMessage1Change(MenuEntry* entry);
    void BaseCreateRecruitmentMessage2Change(MenuEntry* entry);
    void BaseCreateRecruitmentMessage3Change(MenuEntry* entry);
    void BaseCreateRecruitmentMessage4Change(MenuEntry* entry);
    // 集会所を作る終わり

    // 集会所を探す
    void BaseSearchTargetChange(MenuEntry* entry);
    void BaseSearchQuestTypeChange(MenuEntry* entry);
    void BaseSearchHostHunterRankMinimumChange(MenuEntry* entry);
    void BaseSearchHostHunterRankMaximumChange(MenuEntry* entry);
    void BaseSearchInQuestChange(MenuEntry* entry);
    void BaseSearchPasswordExistChange(MenuEntry* entry);
    // 集会所を探す終わり

    // 集会所終わり

    void DisplayBasePassword(MenuEntry* entry);
    void DisplayPlayerCoordinate(MenuEntry* entry);
    void FloatBug(MenuEntry* entry);
    void ViewingAngleChange(MenuEntry* entry);
    void ViewingAngleOption(MenuEntry* entry);
    void ViewingAngleChangeV2(MenuEntry* entry);
    void WeaponSizeChange(MenuEntry* entry);
    void ContrastChange(MenuEntry* entry);
    void GuildCardChange(MenuEntry* entry);
    void RegionChange(MenuEntry* entry);
    void VillageContributionPointChange(MenuEntry* entry);
    void RoomServiceChange(MenuEntry* entry);
    void WallThrough(MenuEntry* entry);
    void MaximumFpsChange(MenuEntry* entry);
    // その他終わり

    // おまけ
    // 変換
    void HexToDecd32(MenuEntry* entry);
    void HexToDecu32(MenuEntry* entry);
    void HexToDecd16(MenuEntry* entry);
    void HexToDecu16(MenuEntry* entry);
    void HexToDecd8(MenuEntry* entry);
    void HexToDecu8(MenuEntry* entry);
    void DecToHex(MenuEntry* entry);
    // 変換終わり

    // 電卓
    void HexadecimalCalculator(MenuEntry* entry);
    void DecimalCalculator(MenuEntry* entry);
    void FloatCalculator(MenuEntry* entry);
    // 電卓終わり

    // RGBチェッカー
    void RedInput(MenuEntry* entry);
    void GreenInput(MenuEntry* entry);
    void BlueInput(MenuEntry* entry);
    void RGBOutput(MenuEntry* entry);
    // RGBチェッカー終わり

    void HexEditor(MenuEntry* entry);
    void HexEditor2(MenuEntry* entry);
    void LocalTimeDisplay(MenuEntry* entry);
    void Information(MenuEntry* entry);
    void TitleID();
    void NameID();
    void ConsoleType();
    void WiFiStatus();
    // おまけ終わり

} // namespace CTRPluginFramework