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

    // �v���C���[
    // �X�e�[�^�X�ύX
    void AttackPowerChange(MenuEntry* entry);
    void AttackPowerOption(MenuEntry* entry);
    void DefencePowerChange(MenuEntry* entry);
    void DefencePowerOption(MenuEntry* entry);
    void AttributeChange(MenuEntry* entry);
    void AttributeOption(MenuEntry* entry);
    void ResistanceChange(MenuEntry* entry);
    void ResistanceOption(MenuEntry* entry);
    // �X�e�[�^�X�ύX�I���

    // �v���C���[���ύX
    // ��Z�ύX
    void HunterArt1Change(MenuEntry* entry);
    void HunterArt2Change(MenuEntry* entry);
    void HunterArt3Change(MenuEntry* entry);
    // ��Z�ύX�I���

    // ���̐F�ύX
    void SkinRedChange(MenuEntry* entry);
    void SkinGreenChange(MenuEntry* entry);
    void SkinBlueChange(MenuEntry* entry);
    void SkinColorChange(MenuEntry* entry);
    // ���̐F�ύX�I���

    // �H��
    // �t���O
    void MealInfinite(MenuEntry* entry);
    void LuxuryCouponGrant(MenuEntry* entry);
    void MeetRequestInfinite(MenuEntry* entry);
    // �t���O�I���

    // �X�e�[�^�X
    // �ϐ�
    void MealFireResistanceUp(MenuEntry* entry);
    void MealWaterResistanceUp(MenuEntry* entry);
    void MealThunderResistanceUp(MenuEntry* entry);
    void MealIceResistanceUp(MenuEntry* entry);
    void MealDragonResistanceUp(MenuEntry* entry);
    // �ϐ��I���

    void MealHpUp(MenuEntry* entry);
    void MealStaminaUp(MenuEntry* entry);
    void MealAttackPowerUp(MenuEntry* entry);
    void MealDefencePowerUp(MenuEntry* entry);
    // �X�e�[�^�X�I���

    void MealSkillChange(MenuEntry* entry);
    // �H���I���

    void PlayerVoiceChange(MenuEntry* entry);
    void PlayerEyeColorChange(MenuEntry* entry);
    void PlayerInnerChange(MenuEntry* entry);
    void PlayerGenderChange(MenuEntry* entry);
    void PlayerHuntingStyleChange(MenuEntry* entry);
    void PlayerHearStyleChange(MenuEntry* entry);
    void PlayerFaceChange(MenuEntry* entry);
    void PlayerMakeChange(MenuEntry* entry);
    // �v���C���[���ύX�I���

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
    // �v���C���[�I���

    // �A�C�e��
    // ����
    // ��ΕҏW
    void AmuletCreate(MenuEntry* entry);
    void AmuletTypeChange(MenuEntry* entry);
    void AmuletSkillChange(MenuEntry* entry);
    void AmuletSkillPointChange(MenuEntry* entry);
    void AmuletSlotChange(MenuEntry* entry);
    // ��ΕҏW�I���

    // ���ҏW
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
    // ���ҏW�I���

    void OtherPlayerEquipmentCopy(MenuEntry* entry);
    // �����I���

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
    // �A�C�e���I���

    // ����
    // ����ʃ`�[�g
    // �K�������X�`�[�g
    void GunlanceHeatGageFix(MenuEntry* entry);
    void GunlanceHeatGageOption(MenuEntry* entry);
    void GunlanceAmmoInfinite(MenuEntry* entry);
    void GunlanceInvalidOverHeat(MenuEntry* entry);
    // �K�������X�`�[�g�I���

    // �������`�[�g
    void InsectGlaiveAlwaysTripleUp(MenuEntry* entry);
    void InsectGlaiveInsectStaminaInfinite(MenuEntry* entry);
    // �������`�[�g�I���

    // �{�E�K���`�[�g
    void BowgunAmmoInfinite(MenuEntry* entry);
    void BowgunCrouchingShot(MenuEntry* entry);
    // �{�E�K���`�[�g�I���

    void ChargeStageFix(MenuEntry* entry);
    void ChageStageOption(MenuEntry* entry);
    void WeaponGageFix(MenuEntry* entry);
    void ChargeAxeBinFix(MenuEntry* entry);
    void HuntingHornAllEffectGrant(MenuEntry* entry);
    // ����ʃ`�[�g�I���

    void AttributePointChange(MenuEntry* entry);
    void NoMotion(MenuEntry* entry);
    void CriticalRate100(MenuEntry* entry);
    void BowgunAutoReload(MenuEntry* entry);
    void InfiniteSharpness(MenuEntry* entry);
    void SharpnessPlus2(MenuEntry* entry);
    void ChargeSpeedUp(MenuEntry* entry);
    void ChargeGageMax(MenuEntry* entry);
    // ����I���

    // �����X�^�[
    // �����X�^�[����ʕ\��
    void Monster1HpDisplay(MenuEntry* entry);
    void Monster2HpDisplay(MenuEntry* entry);
    void Monster1SizeMagnificationDisplay(MenuEntry* entry);
    void Monster2SizeMagnificationDisplay(MenuEntry* entry);
    // �����X�^�[����ʕ\���I���

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
    // �����X�^�[�I���

    // �˂�
    // �˂��ҏW
    void PalicoChoice(MenuEntry* entry);

    // �����T�|�[�g�s��
    void PalicoEquipmentSupportAction1Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction2Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction3Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction4Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction5Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction6Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction7Change(MenuEntry* entry);
    void PalicoEquipmentSupportAction8Change(MenuEntry* entry);
    // �����T�|�[�g�s���I���

    // �����I�g���X�L��
    void PalicoEquipmentSkill1Change(MenuEntry* entry);
    void PalicoEquipmentSkill2Change(MenuEntry* entry);
    void PalicoEquipmentSkill3Change(MenuEntry* entry);
    void PalicoEquipmentSkill4Change(MenuEntry* entry);
    void PalicoEquipmentSkill5Change(MenuEntry* entry);
    void PalicoEquipmentSkill6Change(MenuEntry* entry);
    void PalicoEquipmentSkill7Change(MenuEntry* entry);
    void PalicoEquipmentSkill8Change(MenuEntry* entry);
    // �����I�g���X�L���I���

    // �K���T�|�[�g�s��
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
    // �K���T�|�[�g�s���I���

    // �K���I�g���X�L��
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
    // �K���I�g���X�L���I���

    // ������
    // �����ڂ̐F�ύX
    // �ѐF
    void PalicoBodyHairColorRedChange(MenuEntry* entry);
    void PalicoBodyHairColorGreenChange(MenuEntry* entry);
    void PalicoBodyHairColorBlueChange(MenuEntry* entry);
    // �ѐF�I���

    // �E�ڂ̐F
    void PalicoRightEyeColorRedChange(MenuEntry* entry);
    void PalicoRightEyeColorGreenChange(MenuEntry* entry);
    void PalicoRightEyeColorBlueChange(MenuEntry* entry);
    // �E�ڂ̐F�I���

    // ���ڂ̐F
    void PalicoLeftEyeColorRedChange(MenuEntry* entry);
    void PalicoLeftEyeColorGreenChange(MenuEntry* entry);
    void PalicoLeftEyeColorBlueChange(MenuEntry* entry);
    // ���ڂ̐F�I���

    // �C���i�[�̐F
    void PalicoInnerColorRedChange(MenuEntry* entry);
    void PalicoInnerColorGreenChange(MenuEntry* entry);
    void PalicoInnerColorBlueChange(MenuEntry* entry);
    // �C���i�[�̐F�I���

    // �����ڂ̐F�ύX�I���

    void PalicoVoiceChange(MenuEntry* entry);
    void PalicoEyeChange(MenuEntry* entry);
    void PalicoInnerChange(MenuEntry* entry);
    void PalicoFurCoatChange(MenuEntry* entry);
    void PalicoEarChange(MenuEntry* entry);
    void PalicoTailChange(MenuEntry* entry);
    // �����ڏI���

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
    // �˂��ҏW�I���

    void PalicoAttackPowerMagnificationChange(MenuEntry* entry);
    void PalicoAttackPowerMagnificationOption(MenuEntry* entry);
    void PalicoDefencePowerMagnificationChange(MenuEntry* entry);
    void PalicoDefencePowerMagnificationOption(MenuEntry* entry);
    void PalicoAbsorption(MenuEntry* entry);
    void ProwlerSupportGageMax(MenuEntry* entry);
    // �˂��I���

    // ���̑�
    // �`���b�g
    void ChatInfinite(MenuEntry* entry);
    void ChatConversionChange(MenuEntry* entry);
    void ChatConversionList(MenuEntry* entry);
    // �`���b�g�I���

    // �����ς炢
    void InstantDrunk(MenuEntry* entry);
    void InstantDrunkOption(MenuEntry* entry);
    void Drunk1(MenuEntry* entry);
    // �����ς炢�I���

    // �n���^�[�����N
    void HunterRankChange(MenuEntry* entry);
    void HunterRankPointChange(MenuEntry* entry);
    // �n���^�[�����N�I���

    // �v�[�M�[���t�F�j�[
    void FenyAndPugyClothes(MenuEntry* entry);
    void FenyAndPugyNameChange(MenuEntry* entry);
    // �v�[�M�[���t�F�j�[�I���

    // �N�G�X�g
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
    // �N�G�X�g�I���

    // �W�
    // �W������
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
    // �W������I���

    // �W���T��
    void BaseSearchTargetChange(MenuEntry* entry);
    void BaseSearchQuestTypeChange(MenuEntry* entry);
    void BaseSearchHostHunterRankMinimumChange(MenuEntry* entry);
    void BaseSearchHostHunterRankMaximumChange(MenuEntry* entry);
    void BaseSearchInQuestChange(MenuEntry* entry);
    void BaseSearchPasswordExistChange(MenuEntry* entry);
    // �W���T���I���

    // �W��I���

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
    // ���̑��I���

    // ���܂�
    // �ϊ�
    void HexToDecd32(MenuEntry* entry);
    void HexToDecu32(MenuEntry* entry);
    void HexToDecd16(MenuEntry* entry);
    void HexToDecu16(MenuEntry* entry);
    void HexToDecd8(MenuEntry* entry);
    void HexToDecu8(MenuEntry* entry);
    void DecToHex(MenuEntry* entry);
    // �ϊ��I���

    // �d��
    void HexadecimalCalculator(MenuEntry* entry);
    void DecimalCalculator(MenuEntry* entry);
    void FloatCalculator(MenuEntry* entry);
    // �d��I���

    // RGB�`�F�b�J�[
    void RedInput(MenuEntry* entry);
    void GreenInput(MenuEntry* entry);
    void BlueInput(MenuEntry* entry);
    void RGBOutput(MenuEntry* entry);
    // RGB�`�F�b�J�[�I���

    void HexEditor(MenuEntry* entry);
    void HexEditor2(MenuEntry* entry);
    void LocalTimeDisplay(MenuEntry* entry);
    void Information(MenuEntry* entry);
    void TitleID();
    void NameID();
    void ConsoleType();
    void WiFiStatus();
    // ���܂��I���

} // namespace CTRPluginFramework