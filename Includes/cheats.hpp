#ifndef MHX3GX_INCLUDES_CHEATS_H_
#define MHX3GX_INCLUDES_CHEATS_H

#include <3ds.h>

#include <CTRPluginFramework.hpp>
#include <ctime>
#include <string>
#include <vector>

#include "Helpers.hpp"
#include "csvc.h"
#include "libpon.hpp"
#include "types.h"

namespace CTRPluginFramework {

using CallbackPointer = void (*)(void);
using StringVector = std::vector<std::string>;

bool IsInQuest();

void AttackPowerOption(MenuEntry* entry);
void DefencePowerOption(MenuEntry* entry);
void AttributeOption(MenuEntry* entry);
void ResistanceOption(MenuEntry* entry);

void HunterArt1Change(MenuEntry* entry);
void HunterArt2Change(MenuEntry* entry);
void HunterArt3Change(MenuEntry* entry);

void SkinRedChange(MenuEntry* entry);
void SkinGreenChange(MenuEntry* entry);
void SkinBlueChange(MenuEntry* entry);
void SkinColorChange(MenuEntry* entry);

void MealInfinite(MenuEntry* entry);
void LuxuryCouponGrant(MenuEntry* entry);
void MeetRequestInfinite(MenuEntry* entry);

void MealFireResistanceUp(MenuEntry* entry);
void MealWaterResistanceUp(MenuEntry* entry);
void MealThunderResistanceUp(MenuEntry* entry);
void MealIceResistanceUp(MenuEntry* entry);
void MealDragonResistanceUp(MenuEntry* entry);

void MealHpUp(MenuEntry* entry);
void MealStaminaUp(MenuEntry* entry);
void MealAttackPowerUp(MenuEntry* entry);
void MealDefencePowerUp(MenuEntry* entry);

void MealSkillChange(MenuEntry* entry);

void PlayerVoiceChange(MenuEntry* entry);
void PlayerEyeColorChange(MenuEntry* entry);
void PlayerInnerChange(MenuEntry* entry);
void PlayerGenderChange(MenuEntry* entry);
void PlayerHuntingStyleChange(MenuEntry* entry);
void PlayerHearStyleChange(MenuEntry* entry);
void PlayerFaceChange(MenuEntry* entry);
void PlayerCosmeticsChange(MenuEntry* entry);

void PlayerAttackPowerMagnificationOption(MenuEntry* entry);
void PlayerDefencePowerMagnificationOption(MenuEntry* entry);
void PlayerSpeedOption(MenuEntry* entry);
void PlayerCoordinateModifier(MenuEntry* entry);
void PlayerMoonJump(MenuEntry* entry);
void Teleport(MenuEntry* entry);
void Stalker(MenuEntry* entry);
void Repeatmove(MenuEntry* entry);
void HunterArtRelease(MenuEntry* entry);
void HungryInvalid(MenuEntry* entry);
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

void AmuletCreate(MenuEntry* entry);
void AmuletTypeChange(MenuEntry* entry);
void AmuletSkillChange(MenuEntry* entry);
void AmuletSkillPointChange(MenuEntry* entry);
void AmuletSlotChange(MenuEntry* entry);

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

void OtherPlayerEquipmentCopy(MenuEntry* entry);

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
void PorchAllClear(MenuEntry* entry);
void SpecialPermitQuestTicketChange(MenuEntry* entry);

void GunlanceHeatGageOption(MenuEntry* entry);
void GunlanceAmmoInfinite(MenuEntry* entry);
void GunlanceInvalidOverHeat(MenuEntry* entry);

void InsectGlaiveAlwaysTripleUp(MenuEntry* entry);
void InsectGlaiveInsectStaminaInfinite(MenuEntry* entry);

void BowgunAmmoInfinite(MenuEntry* entry);
void BowgunCrouchingShot(MenuEntry* entry);

void ChageStageOption(MenuEntry* entry);
void WeaponGageFix(MenuEntry* entry);
void ChargeAxeBinFix(MenuEntry* entry);
void HuntingHornAllEffectGrant(MenuEntry* entry);

void AttributePointChange(MenuEntry* entry);
void NoMotion(MenuEntry* entry);
void CriticalRate100(MenuEntry* entry);
void BowgunAutoReload(MenuEntry* entry);
void InfiniteSharpness(MenuEntry* entry);
void SharpnessPlus2(MenuEntry* entry);
void ChargeSpeedUp(MenuEntry* entry);
void ChargeGageMax(MenuEntry* entry);

void Monster1HpDisplay(MenuEntry* entry);
void Monster2HpDisplay(MenuEntry* entry);
void Monster1SizeMagnificationDisplay(MenuEntry* entry);
void Monster2SizeMagnificationDisplay(MenuEntry* entry);

void RideGageMax(MenuEntry* entry);
void MonsterCoordinateModifier(MenuEntry* entry);
void MonsterStalker(MenuEntry* entry);
void MonsterActionRepeat(MenuEntry* entry);
void MonsterActionRepeatOption(MenuEntry* entry);
void Monster1And2Stop(MenuEntry* entry);
void Monster1SizeOption(MenuEntry* entry);
void Monster2SizeOption(MenuEntry* entry);
void Monster1SpeedAttributeOption(MenuEntry* entry);
void Monster2SpeedAttributeOption(MenuEntry* entry);
void Monster1And2AlwaysPoison(MenuEntry* entry);
void Monster1And2AlwaysParalysis(MenuEntry* entry);
void Monster1And2AlwaysSleep(MenuEntry* entry);
void Monster1And2AlwaysInvisible(MenuEntry* entry);
void OneAttackKill(MenuEntry* entry);

void PalicoChoice(MenuEntry* entry);

void PalicoEquipmentSupportAction1Change(MenuEntry* entry);
void PalicoEquipmentSupportAction2Change(MenuEntry* entry);
void PalicoEquipmentSupportAction3Change(MenuEntry* entry);
void PalicoEquipmentSupportAction4Change(MenuEntry* entry);
void PalicoEquipmentSupportAction5Change(MenuEntry* entry);
void PalicoEquipmentSupportAction6Change(MenuEntry* entry);
void PalicoEquipmentSupportAction7Change(MenuEntry* entry);
void PalicoEquipmentSupportAction8Change(MenuEntry* entry);

void PalicoEquipmentSkill1Change(MenuEntry* entry);
void PalicoEquipmentSkill2Change(MenuEntry* entry);
void PalicoEquipmentSkill3Change(MenuEntry* entry);
void PalicoEquipmentSkill4Change(MenuEntry* entry);
void PalicoEquipmentSkill5Change(MenuEntry* entry);
void PalicoEquipmentSkill6Change(MenuEntry* entry);
void PalicoEquipmentSkill7Change(MenuEntry* entry);
void PalicoEquipmentSkill8Change(MenuEntry* entry);

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

void PalicoBodyHairColorRedChange(MenuEntry* entry);
void PalicoBodyHairColorGreenChange(MenuEntry* entry);
void PalicoBodyHairColorBlueChange(MenuEntry* entry);

void PalicoRightEyeColorRedChange(MenuEntry* entry);
void PalicoRightEyeColorGreenChange(MenuEntry* entry);
void PalicoRightEyeColorBlueChange(MenuEntry* entry);

void PalicoLeftEyeColorRedChange(MenuEntry* entry);
void PalicoLeftEyeColorGreenChange(MenuEntry* entry);
void PalicoLeftEyeColorBlueChange(MenuEntry* entry);

void PalicoInnerColorRedChange(MenuEntry* entry);
void PalicoInnerColorGreenChange(MenuEntry* entry);
void PalicoInnerColorBlueChange(MenuEntry* entry);

void PalicoVoiceChange(MenuEntry* entry);
void PalicoEyeChange(MenuEntry* entry);
void PalicoInnerChange(MenuEntry* entry);
void PalicoFurCoatChange(MenuEntry* entry);
void PalicoEarChange(MenuEntry* entry);
void PalicoTailChange(MenuEntry* entry);

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

void PalicoAttackPowerMagnificationOption(MenuEntry* entry);
void PalicoDefencePowerMagnificationOption(MenuEntry* entry);
void PalicoAbsorption(MenuEntry* entry);
void ProwlerSupportGageMax(MenuEntry* entry);

void ChatInfinite(MenuEntry* entry);
void ChatConversionChange(MenuEntry* entry);
void ChatConversionList(MenuEntry* entry);

void InstantDrunk(MenuEntry* entry);
void InstantDrunkOption(MenuEntry* entry);
void Drunk1(MenuEntry* entry);

void HunterRankChange(MenuEntry* entry);
void HunterRankPointChange(MenuEntry* entry);

void FenyAndPugyClothes(MenuEntry* entry);
void FenyAndPugyNameChange(MenuEntry* entry);

void QuestClearOption(MenuEntry* entry);
void QuestWaitSkip(MenuEntry* entry);
void QuestResultSkip(MenuEntry* entry);
void QuestDownMaxOption(MenuEntry* entry);
void QuestDownNowOption(MenuEntry* entry);
void QuestTimeDisplay(MenuEntry* entry);
void SaveScreenOption(MenuEntry* entry);
void QuestTimeStop(MenuEntry* entry);
void AllQuestClearChange(MenuEntry* entry);

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

void BaseSearchTargetChange(MenuEntry* entry);
void BaseSearchQuestTypeChange(MenuEntry* entry);
void BaseSearchHostHunterRankMinimumChange(MenuEntry* entry);
void BaseSearchHostHunterRankMaximumChange(MenuEntry* entry);
void BaseSearchInQuestChange(MenuEntry* entry);
void BaseSearchPasswordExistChange(MenuEntry* entry);

void DisplayBasePassword(MenuEntry* entry);
void DisplayPlayerCoordinate(MenuEntry* entry);
void FloatBug(MenuEntry* entry);
void ViewingAngleOption(MenuEntry* entry);
void ViewingAngleChangeV2(MenuEntry* entry);
void WeaponSizeChange(MenuEntry* entry);
void ContrastChange(MenuEntry* entry);

void GuildCardTitleChange();
void GuildCardClearCount(int choice);
void GuildCardClearCountChange();
void GuildCardPassingCommunicationCountChange();
void GuildCardFriendshipPointChange();
void GuildCardBackGroundInvisible();
void GuildCardTPose();
void GuildCardWeaponUseCountWeaponSelect(int group);
void GuildCardWeaponUseCountChange(int group, int choice);
void GuildCardWeaponUseCountMax();
void GuildCardWeaponUseCountChanger();
void GuildCardPlayTimeChange();
void GuildCardMonsterHuntingCountChanger();
void GuildCardSmallMonsterHuntingCountChange();
void GuildCardMonsterHuntingCountChange(
    const std::vector<std::string>& listGuildCardChangeMonsterHuntingBig);
void GuildCardMonsterCaptureCountChange(
    const std::vector<std::string>& listGuildCardChangeMonsterHuntingBig);
void GuildCardMonsterHuntingCountMax();
void GuildCardMonsterHuntingCountChanger();
void GuildCardChange(MenuEntry* entry);

void RegionChange(MenuEntry* entry);
void VillageContributionPointChange(MenuEntry* entry);
void RoomServiceChange(MenuEntry* entry);
void WallThrough(MenuEntry* entry);
void MaximumFpsChange(MenuEntry* entry);

void HexToDecd32(MenuEntry* entry);
void HexToDecu32(MenuEntry* entry);
void HexToDecd16(MenuEntry* entry);
void HexToDecu16(MenuEntry* entry);
void HexToDecd8(MenuEntry* entry);
void HexToDecu8(MenuEntry* entry);
void DecToHex(MenuEntry* entry);

void HexadecimalCalculator(MenuEntry* entry);
void DecimalCalculator(MenuEntry* entry);
void DoubleCalculator(MenuEntry* entry);

int RedInput();
int GreenInput();
int BlueInput();
void RGBOutput(MenuEntry* entry);

void HexEditor(MenuEntry* entry);
void LocalTimeDisplay(MenuEntry* entry);
void Information(MenuEntry* entry);
void TitleID();
void ProcessNameID();
void ConsoleType();
void WiFiStatus();
void BatteryLevel();

}  // namespace CTRPluginFramework

#endif  // MHX3GX_INCLUDES_CHEATS_H