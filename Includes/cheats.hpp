#ifndef MHX3GX_INCLUDES_CHEATS_HPP_
#define MHX3GX_INCLUDES_CHEATS_HPP_

#include "stdafx.hpp"

namespace CTRPluginFramework {

std::vector<std::string> GetListPalicoSkill();
std::vector<std::string> GetListPalicoAction();
std::vector<std::string> GetListToggle();

bool IsInQuest();

void AttackPowerOption(MenuEntry *entry);
void DefencePowerOption(MenuEntry *entry);
void AttributeOption(MenuEntry *entry);
void ResistanceOption(MenuEntry *entry);

void HunterArt1Change(MenuEntry *entry);
void HunterArt2Change(MenuEntry *entry);
void HunterArt3Change(MenuEntry *entry);

void SkinRedChange(MenuEntry *entry);
void SkinGreenChange(MenuEntry *entry);
void SkinBlueChange(MenuEntry *entry);
void SkinColorChange(MenuEntry *entry);

void MealInfinite(MenuEntry *entry);
void LuxuryCouponGrant(MenuEntry *entry);
void MeetRequestInfinite(MenuEntry *entry);

void MealFireResistanceUp(MenuEntry *entry);
void MealWaterResistanceUp(MenuEntry *entry);
void MealThunderResistanceUp(MenuEntry *entry);
void MealIceResistanceUp(MenuEntry *entry);
void MealDragonResistanceUp(MenuEntry *entry);

void MealHpUp(MenuEntry *entry);
void MealStaminaUp(MenuEntry *entry);
void MealAttackPowerUp(MenuEntry *entry);
void MealDefencePowerUp(MenuEntry *entry);

void MealSkillChange(MenuEntry *entry);

void PlayerVoiceChange(MenuEntry *entry);
void PlayerEyeColorChange(MenuEntry *entry);
void PlayerInnerChange(MenuEntry *entry);
void PlayerGenderChange(MenuEntry *entry);
void PlayerHuntingStyleChange(MenuEntry *entry);
void PlayerHearStyleChange(MenuEntry *entry);
void PlayerFaceChange(MenuEntry *entry);
void PlayerCosmeticsChange(MenuEntry *entry);

void PlayerAttackPowerMagnificationOption(MenuEntry *entry);
void PlayerDefencePowerMagnificationOption(MenuEntry *entry);
void PlayerSpeedOption(MenuEntry *entry);
void PlayerCoordinateModifier(MenuEntry *entry);
void PlayerMoonJump(MenuEntry *entry);
void Teleport(MenuEntry *entry);
void Stalker(MenuEntry *entry);
void RepeatMove(MenuEntry *entry);
void HunterArtRelease(MenuEntry *entry);
void HungryInvalid(MenuEntry *entry);
void HunterSizeOption(MenuEntry *entry);
void InfiniteHp(MenuEntry *entry);
void Invincible(MenuEntry *entry);
void SuperArmor(MenuEntry *entry);
void InfiniteStamina(MenuEntry *entry);
void InfiniteHunterArt(MenuEntry *entry);
void Always3HunterArtEquip(MenuEntry *entry);
void AlwaysDisplayMap(MenuEntry *entry);
void AlwaysPaint(MenuEntry *entry);
void SpeedHack(MenuEntry *entry);
void InQuestSpeedHack(MenuEntry *entry);
void IfRunMoonWalk(MenuEntry *entry);
void HunterNameChange(MenuEntry *entry);
void PlayerReceivedDamageChange(MenuEntry *entry);

void AmuletCreate(MenuEntry *entry);
void AmuletTypeChange(MenuEntry *entry);
void AmuletSkillChange(MenuEntry *entry);
void AmuletSkillPointChange(MenuEntry *entry);
void AmuletSlotChange(MenuEntry *entry);

void InsectTypeChange(MenuEntry *entry);
void InsectLevelChange(MenuEntry *entry);
void InsectPowerChange(MenuEntry *entry);
void InsectWeightChange(MenuEntry *entry);
void InsectStaminaChange(MenuEntry *entry);
void InsectFireAttributeChange(MenuEntry *entry);
void InsectWaterAttributeChange(MenuEntry *entry);
void InsectThunderAttributeChange(MenuEntry *entry);
void InsectIceAttributeChange(MenuEntry *entry);
void InsectDragonAttributeChange(MenuEntry *entry);

void OtherPlayerEquipmentCopy(MenuEntry *entry);

void InfiniteBombPut(MenuEntry *entry);
void TanhoreItemSet(MenuEntry *entry);
void MoneyChange(MenuEntry *entry);
void WycademyPointChange(MenuEntry *entry);
void InfiniteItemAmmo(MenuEntry *entry);
void NoMaterialCompound(MenuEntry *entry);
void CargoPutInPorch(MenuEntry *entry);
void InfiniteCollect(MenuEntry *entry);
void NoMaterialEquipmentCreate(MenuEntry *entry);
void EquipmentAllRelease(MenuEntry *entry);
void AllItemSold(MenuEntry *entry);
void ItemBox1400Expansion(MenuEntry *entry);
void HaveItem99(MenuEntry *entry);
u8 ItemBoxHorizontalIndex();
u8 ItemBoxVerticalIndex();
void ItemBoxCanEquipmentChange(MenuEntry *entry);
void ItemBoxEdit(MenuEntry *entry);
void MySetToPorchItemCopy(MenuEntry *entry);
void DeliveryItemToPorchCopy(MenuEntry *entry);
void PorchAllClear(MenuEntry *entry);
void SpecialPermitQuestTicketChange(MenuEntry *entry);

void GunlanceHeatGageOption(MenuEntry *entry);
void GunlanceAmmoInfinite(MenuEntry *entry);
void GunlanceInvalidOverHeat(MenuEntry *entry);

void InsectGlaiveAlwaysTripleUp(MenuEntry *entry);
void InsectGlaiveInsectStaminaInfinite(MenuEntry *entry);

void BowgunAmmoInfinite(MenuEntry *entry);
void BowgunCrouchingShot(MenuEntry *entry);

void ChargeStageOption(MenuEntry *entry);
void WeaponGageFix(MenuEntry *entry);
void ChargeAxeBinFix(MenuEntry *entry);
void HuntingHornAllEffectGrant(MenuEntry *entry);

void AttributePointChange(MenuEntry *entry);
void NoMotion(MenuEntry *entry);
void CriticalRate100(MenuEntry *entry);
void BowgunAutoReload(MenuEntry *entry);
void InfiniteSharpness(MenuEntry *entry);
void SharpnessPlus2(MenuEntry *entry);
void ChargeSpeedUp(MenuEntry *entry);
void ChargeGageMax(MenuEntry *entry);

void Monster1HpDisplay(MenuEntry *entry);
void Monster2HpDisplay(MenuEntry *entry);
void Monster1SizeMagnificationDisplay(MenuEntry *entry);
void Monster2SizeMagnificationDisplay(MenuEntry *entry);

void RideGageMax(MenuEntry *entry);
void MonsterCoordinateModifier(MenuEntry *entry);
void MonsterStalker(MenuEntry *entry);
void MonsterActionRepeatOption(MenuEntry *entry);
void Monster1And2Stop(MenuEntry *entry);
void Monster1SizeOption(MenuEntry *entry);
void Monster2SizeOption(MenuEntry *entry);
void Monster1SpeedAttributeOption(MenuEntry *entry);
void Monster2SpeedAttributeOption(MenuEntry *entry);
void Monster1And2AlwaysPoison(MenuEntry *entry);
void Monster1And2AlwaysParalysis(MenuEntry *entry);
void Monster1And2AlwaysSleep(MenuEntry *entry);
void Monster1And2AlwaysInvisible(MenuEntry *entry);
void OneAttackKill(MenuEntry *entry);

void PalicoChoice(MenuEntry *entry);

std::vector<std::string> GetPalicoEquipmentSupportAction();
void PalicoEquipmentSupportActionChange(int number);
void PalicoEquipmentSupportActionChanger(MenuEntry *entry);

std::vector<std::string> GetPalicoEquipmentSkill();
void PalicoEquipmentSkillChange(int number);
void PalicoEquipmentSkillChanger(MenuEntry *entry);

std::vector<std::string> GetPalicoLearnSupportAction();
void PalicoLearnSupportActionChange(int number);
void PalicoLearnSupportActionChanger(MenuEntry *entry);

std::vector<std::string> GetPalicoLearnSkill();
void PalicoLearnSkillChange(int number);
void PalicoLearnSkillChanger(MenuEntry *entry);

void PalicoBodyHairColorChange(int choice);
void PalicoBodyHairColorChanger(MenuEntry *entry);

void PalicoRightEyeColorChange(int choice);
void PalicoRightEyeColorChanger(MenuEntry *entry);

void PalicoLeftEyeColorChange(int choice);
void PalicoLeftEyeColorChanger(MenuEntry *entry);

void PalicoInnerColorChange(int choice);
void PalicoInnerColorChanger(MenuEntry *entry);

void PalicoVoiceChange(MenuEntry *entry);
void PalicoEyeChange(MenuEntry *entry);
void PalicoInnerChange(MenuEntry *entry);
void PalicoFurCoatChange(MenuEntry *entry);
void PalicoEarChange(MenuEntry *entry);
void PalicoTailChange(MenuEntry *entry);

void PalicoExperienceChange(MenuEntry *entry);
void PalicoLevelChange(MenuEntry *entry);
void PalicoSupportTrendChange(MenuEntry *entry);
void PalicoClosenessChange(MenuEntry *entry);
void PalicoTargetChange(MenuEntry *entry);
void PalicoCommentEditPossibleChange(MenuEntry *entry);
void SpecialDeliveryDisplayChange(MenuEntry *entry);
void PalicoNameChange(MenuEntry *entry);
void PalicoCommentChange(MenuEntry *entry);
void PalicoGodParentChange(MenuEntry *entry);
void PalicoPredecessorHusbandChange(MenuEntry *entry);

void PalicoAttackPowerMagnificationOption(MenuEntry *entry);
void PalicoDefencePowerMagnificationOption(MenuEntry *entry);
void PalicoAbsorption(MenuEntry *entry);
void ProwlerSupportGageMax(MenuEntry *entry);

void ChatInfinite(MenuEntry *entry);
void ChatConversionChange(MenuEntry *entry);
void ChatConversionList(MenuEntry *entry);

void InstantDrunkOption(MenuEntry *entry);
void Drunk1(MenuEntry *entry);

void HunterRankChange(MenuEntry *entry);
void HunterRankPointChange(MenuEntry *entry);

void FenyAndPugyClothes(MenuEntry *entry);
void FenyAndPugyNameChange(MenuEntry *entry);

void QuestClearOption(MenuEntry *entry);
void QuestWaitSkip(MenuEntry *entry);
void QuestResultSkip(MenuEntry *entry);
void QuestDownMaxOption(MenuEntry *entry);
void QuestDownNowOption(MenuEntry *entry);
void QuestTimeDisplay(MenuEntry *entry);
void SaveScreenOption(MenuEntry *entry);
void QuestTimeStop(MenuEntry *entry);
void AllQuestClearChange(MenuEntry *entry);

void BaseCreateTargetChange(MenuEntry *entry);
void BaseCreateQuestTypeChange(MenuEntry *entry);
void BaseCreateRecruitmentHunterRankMinimumChange(MenuEntry *entry);
void BaseCreateRecruitmentHunterRankMaximumChange(MenuEntry *entry);
void BaseCreateEntryPeopleChange(MenuEntry *entry);
void BaseCreateEntryLimitChange(MenuEntry *entry);
void BaseCreatePasswordExistChange(MenuEntry *entry);
void BaseCreateRecruitmentMessage1Change(MenuEntry *entry);
void BaseCreateRecruitmentMessage2Change(MenuEntry *entry);
void BaseCreateRecruitmentMessage3Change(MenuEntry *entry);
void BaseCreateRecruitmentMessage4Change(MenuEntry *entry);

void BaseSearchTargetChange(MenuEntry *entry);
void BaseSearchQuestTypeChange(MenuEntry *entry);
void BaseSearchHostHunterRankMinimumChange(MenuEntry *entry);
void BaseSearchHostHunterRankMaximumChange(MenuEntry *entry);
void BaseSearchInQuestChange(MenuEntry *entry);
void BaseSearchPasswordExistChange(MenuEntry *entry);

void DisplayPlayerCoordinate(MenuEntry *entry);
void ViewingAngleOption(MenuEntry *entry);
void ViewingAngleChangeV2(MenuEntry *entry);
void WeaponSizeChange(MenuEntry *entry);
void ContrastChange(MenuEntry *entry);

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
void GuildCardSmallMonsterHuntingCountChange();
void GuildCardMonsterHuntingCountChange(
    const std::vector<std::string> &list_guild_card_change_monster_hunt_big);
void GuildCardMonsterCaptureCountChange(
    const std::vector<std::string> &list_guild_card_change_monster_hunt_big);
void GuildCardMonsterHuntingCountMax();
void GuildCardMonsterHuntingCountChanger();
void GuildCardChange(MenuEntry *entry);

void RegionChange(MenuEntry *entry);
void VillageContributionPointChange(MenuEntry *entry);
void RoomServiceChange(MenuEntry *entry);
void WallThrough(MenuEntry *entry);
void MaximumFpsChange(MenuEntry *entry);

void HexToDecD32(MenuEntry *entry);
void HexToDecU32(MenuEntry *entry);
void HexToDecD16(MenuEntry *entry);
void HexToDecU16(MenuEntry *entry);
void HexToDecD8(MenuEntry *entry);
void HexToDecU8(MenuEntry *entry);
void DecToHex(MenuEntry *entry);

void HexadecimalCalculator(MenuEntry *entry);
void DecimalCalculator(MenuEntry *entry);
void DoubleCalculator(MenuEntry *entry);

int RedInput();
int GreenInput();
int BlueInput();
void RgbOutput(MenuEntry *entry);

void HexEditor(MenuEntry *entry);
void LocalTimeDisplay(MenuEntry *entry);
void Information(MenuEntry *entry);
void TitleId();
void ProcessNameId();
void ConsoleType();
void WiFiStatus();
void BatteryLevel();

}  // namespace CTRPluginFramework

#endif  // MHX3GX_INCLUDES_CHEATS_HPP_