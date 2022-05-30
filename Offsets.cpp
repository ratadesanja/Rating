#include "Offsets.h" // 12.10
const int oGameTime = 0x3101D6C;
const int oObjectManager = 0x24B9B48;
const int oAttackableUnitList = 0x24B9B7C; //A1 ?? ?? ?? ?? 8B 50 04 8B 40 08
const int oLocalPlayer = 0x31085EC;
const int oUnderMouseObject = 0x24B9D44; 
const int oChat = 0x3108EC8;
const int oViewMatrix = 0x3136fc8;
const int oViewProjMatrices = 0x3135ED0; 
const int oRenderer = 0x3138D54; 
const int oMinimapObject = 0x3101DAC; 
const int oGameClient = 0x24A8234;
const int ZoomClass = 0x31012BC;

const int oGameState = 0x8;
const int oChatIsOpen = 0x75C;

const int oObjIndex = 0x8;
const int oObjTeam = 0x34;
const int oObjMissileName = 0x54;
const int oObjNetworkID = 0xB4;
const int oObjPos = 0x1DC;
const int oObjMissileSpellCast = 0x250;
const int oObjVisibility = 0x274;
const int oObjSpawnCount = 0x288;
const int oObjSrcIndex = 0x294;
const int oObjMana = 0x29C;
const int oObjMaxMana = 0x2AC;
const int oObjRecallState = 0xD60;
const int oObjHealth = 0xD9C;
const int oObjMaxHealth = 0xDAC;
const int oObjAbilityHaste = 0x16A0;

const int oObjLethality = 0x11A8;
const int oObjArmor = 0x1294;
const int oObjBonusArmor = 0x1298;

const int oObjMagicRes = 0x129C;
const int oObjBonusMagicRes = 0x12A0;
const int oObjBaseAtk = 0x126C;
const int oObjBonusAtk = 0x11E4;
const int oObjMoveSpeed = 0x12AC;
const int oObjSpellBook = 0x26C4; //0x27C0
const int oObjTransformation = 0x3040;
const int oObjName = 0x2ABC;
const int oObjLvl = 0x329C;
const int oObjExpiry = 0x298;
const int oObjCrit = 0x12C8;
const int oObjCritMulti = 0x12B8;
const int oObjAbilityPower = 0x1750;
const int oObjBonusAtkSpeed = 0x1280;
const int oObjAtkSpeedMulti = 0x1268;
const int oObjAtkRange = 0x12B4;
const int oObjTargetable = 0xD04;
const int oObjInvulnerable = 0x3D4;
const int oObjIsMoving = 0x32E7;
const int oObjDirection = 0x1B88;
const int oObjItemList = 0x33E8;
const int oObjExperience = 0x337C;
const int oObjMagicPen = 0x11E4;
const int oObjMagicPenMulti = 0x1248;
const int oObjAdditionalApMulti = 0x1248;
const int oObjManaRegen = 0x1150;
const int oObjHealthRegen = 0x1280;

const int oObjBuffManager = 0x2098; // 0x2180;
const int oBuffManagerEntriesArray = 0x10;
const int oBuffEntryBuff = 0x8;
const int oBuffType = 0x4;
const int oBuffEntryBuffStartTime = 0xC;
const int oBuffEntryBuffEndTime = 0x10;
const int oBuffEntryBuffCount = 0x74;
const int oBuffEntryBuffCountAlt = 0x24;
const int oBuffEntryBuffCountAlt2 = 0;
const int oBuffName = 0x8;
const int oBuffEntryBuffNodeStart = 0x20;
const int oBuffEntryBuffNodeCurrent = 0x24;

const int oItemListItem = 0xC;
const int oItemInfo = 0x20;
const int oItemInfoId = 0x68;

const int oRendererWidth = 0xC;
const int oRendererHeight = 0x10;

const int oSpellBookActiveSpellCast = 0x20;
const int oSpellBookSpellSlots = 0x478;
const int oSpellSlotLevel = 0x1C;
const int oSpellSlotTime = 0x24;
const int oSpellSlotCharges = 0x54;
const int oSpellSlotTimeCharge = 0x74;
const int oSpellSlotDamage = 0x94;
const int oSpellSlotSpellInfo = 0x120;
const int oSpellInfoSpellData = 0x40; // 0x44
const int oSpellDataSpellName = 0x6C;
const int oSpellDataMissileName = 0x6C;
const int oSpellSlotSmiteTimer = 0x64;
const int oSpellSlotSmiteCharges = 0x58;
const int oSpellCastSpellInfo = 0x8;
const int oSpellCastStartTime = 0x544;
const int oSpellCastStartTimeAlt = 0x534;
const int oSpellCastCastTime = 0x4C0;
const int oSpellCastStart = 0x80;
const int oSpellCastEnd = 0x8C;
const int oSpellCastSrcIdx = 0x68;
const int oSpellCastDestIdx = 0xC0;

const int oObjectMapCount = 0x2C;
const int oObjectMapRoot = 0x28;
const int oObjectMapNodeNetId = 0x10;
const int oObjectMapNodeObject = 0x14;

const int oMissileSpellInfo = 0x278;
const int oMissileSrcIdx = 0x2DC;
const int oMissileDestIdx = 0x330;
const int oMissileStartPos = 0x2F4;
const int oMissileEndPos = 0x300;

const int oMinimapObjectHud = 0x120;
const int oMinimapHudPos = 0x44;
const int oMinimapHudSize = 0x4C;