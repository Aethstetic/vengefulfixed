#include "csgostructs.hpp"
#include "../helpers/math.hpp"
#include "../helpers/utils.hpp"
#include "../Helpers/math.hpp"
#include <array>


bool C_BaseEntity::IsEnemy()
{
	if (!g_LocalPlayer)
		return false;

	return (this->m_iTeamNum() != g_LocalPlayer->m_iTeamNum());
}

bool C_BaseEntity::IsPlayer()
{
    //index: 152
    //ref: "effects/nightvision"
    //sig: 8B 92 ? ? ? ? FF D2 84 C0 0F 45 F7 85 F6
    return CallVFunction<bool(__thiscall*)(C_BaseEntity*)>(this, 152)(this);
}

bool C_BaseEntity::IsWeapon()
{
    //index: 160
    //ref: "CNewParticleEffect::DrawModel"
    //sig: 8B 80 ? ? ? ? FF D0 84 C0 74 6F 8B 4D A4
    return CallVFunction<bool(__thiscall*)(C_BaseEntity*)>(this, 160)(this);
}

void C_BasePlayer::SetAbsAngles(const QAngle& angles)
{
	if (!this)
		return;
	typedef void(__thiscall* SetAbsAnglesFn)(C_BasePlayer*, const QAngle&);
	static SetAbsAnglesFn SetAbsAngles = (SetAbsAnglesFn)Utils::PatternScan(GetModuleHandle("client_panorama.dll"),"55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
	if (!SetAbsAngles)
		return;
	SetAbsAngles(this, angles);
	
}

void C_BasePlayer::SetPoseAngles(float_t yaw, float_t pitch)
{
	auto &poses = m_flPoseParameter();
	poses[11] = (pitch + 90) / 180;
	poses[2] = (yaw + 180) / 360;
}


void C_BasePlayer::SetAbsOrigin(const Vector &origin)
{
	if (!this)
		return;
	using SetAbsOriginFn = void(__thiscall*)(C_BasePlayer*, const Vector &origin);
	static SetAbsOriginFn SetAbsOrigin = (SetAbsOriginFn)Utils::PatternScan(GetModuleHandle("client_panorama.dll"), "55 8B EC 83 E4 F8 51 53 56 57 8B F1");
	if (!SetAbsOrigin)
		return;
	SetAbsOrigin(this, origin);
}

void C_BasePlayer::InvalidateBoneCache()
{
	static DWORD invalKostCache = (DWORD)Utils::PatternScan(GetModuleHandle("client_panorama.dll"), "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");
	unsigned long g_iModelBoneCounter = **(unsigned long**)(invalKostCache + 10);
	*(unsigned int*)((DWORD)this + 0x2914) = 0xFF7FFFFF; // m_flLastBoneSetupTime = -FLT_MAX;
	*(unsigned int*)((DWORD)this + 0x2680) = (g_iModelBoneCounter - 1); // m_iMostRecentModelBoneCounter = g_iModelBoneCounter - 1;
}


bool C_BaseEntity::IsPlantedC4()
{
    return GetClientClass()->m_ClassID == ClassId_CPlantedC4;
}

bool C_BaseEntity::IsDefuseKit()
{
    return GetClientClass()->m_ClassID == ClassId_CBaseAnimating;
}
CCSWeaponInfo* C_BaseCombatWeapon::GetCSWeaponData()
{
	static auto fnGetWpnData
		= reinterpret_cast<CCSWeaponInfo*(__thiscall*)(void*)>(
			Utils::PatternScan(GetModuleHandleW(L"client_panorama.dll"), "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B")
			);
	return fnGetWpnData(this);
}

bool C_BaseCombatWeapon::HasBullets()
{
	return !IsReloading() && m_iClip1() > 0;
}

bool C_BaseCombatWeapon::CanFire()
{
	if (IsReloading() || m_iClip1() <= 0)
		return false;

	if (!g_LocalPlayer)
		return false;

	float flServerTime = g_LocalPlayer->m_nTickBase() * g_GlobalVars->interval_per_tick;

	return m_flNextPrimaryAttack() <= flServerTime;
}

bool C_BaseCombatWeapon::IsGrenade()
{
	return GetCSWeaponData()->WeaponType == WEAPONTYPE_GRENADE;
}

bool C_BaseCombatWeapon::IsKnife()
{
	return GetCSWeaponData()->WeaponType == WEAPONTYPE_KNIFE;
}

bool C_BaseCombatWeapon::IsRifle()
{
	switch (GetCSWeaponData()->WeaponType)
	{
	case WEAPONTYPE_RIFLE:
	case WEAPONTYPE_SHOTGUN:
	case WEAPONTYPE_SUBMACHINEGUN:
	case WEAPONTYPE_MACHINEGUN:
		return true;
	default:
		return false;
	}
}

void C_BasePlayer::UpdateClientSideAnimation()
{
	typedef void(__thiscall *o_updateClientSideAnimation)(void*);
	CallVFunction<o_updateClientSideAnimation>(this, 218)(this);
}



bool C_BaseCombatWeapon::IsPistol()
{
	return GetCSWeaponData()->WeaponType == WEAPONTYPE_PISTOL;
}

bool C_BaseCombatWeapon::IsSniper()
{
	return GetCSWeaponData()->WeaponType == WEAPONTYPE_SNIPER_RIFLE;
}

bool C_BaseCombatWeapon::IsReloading()
{
	static auto inReload = *(uint32_t*)(Utils::PatternScan(GetModuleHandleW(L"client_panorama.dll"), "C6 87 ? ? ? ? ? 8B 06 8B CE FF 90") + 2);
	return *(bool*)((uintptr_t)this + inReload);
}

float C_BaseCombatWeapon::GetInaccuracy()
{
	if (!this)
		return 10000.0f;

	return CallVFunction<float(__thiscall*)(void*)>(this, 467)(this);
}


float C_BaseCombatWeapon::GetSpread()
{
	if (!this)
		return 10000.0f;

	return CallVFunction<float(__thiscall*)(void*)>(this, 436)(this);
}
int C_BaseCombatWeapon::GetItemDefinitionIndex()
{
	return *(int*)((DWORD)this + 0x2F88);
}

void C_BaseCombatWeapon::UpdateAccuracyPenalty()
{
	if (!this)
		return;

	typedef void(__thiscall* OriginFN)(void*);
	CallVFunction<OriginFN>(this, 468)(this);
}


CUserCmd*& C_BasePlayer::m_pCurrentCommand()
{
    static auto currentCommand = *(uint32_t*)(Utils::PatternScan(GetModuleHandleW(L"client_panorama.dll"), "89 BE ? ? ? ? E8 ? ? ? ? 85 FF") + 2);
    return *(CUserCmd**)((uintptr_t)this + currentCommand);
}

Vector C_BasePlayer::GetEyePos()
{
    return m_vecOrigin() + m_vecViewOffset();
}

player_info_t C_BasePlayer::GetPlayerInfo()
{
    player_info_t info;
    g_EngineClient->GetPlayerInfo(EntIndex(), &info);
    return info;
}

bool C_BasePlayer::IsAlive()
{
    return m_lifeState() == LIFE_ALIVE;
}

bool C_BasePlayer::HasC4()
{
    static auto fnHasC4
        = reinterpret_cast<bool(__thiscall*)(void*)>(
            Utils::PatternScan(GetModuleHandleW(L"client_panorama.dll"), "56 8B F1 85 F6 74 31")
            );

    return fnHasC4(this);
}

AnimationLayer *C_BasePlayer::GetAnimOverlays()
{
	// to find offset: use 9/12/17 dll
	// sig: 55 8B EC 51 53 8B 5D 08 33 C0
	return *(AnimationLayer**)((DWORD)this + 10608);
}

AnimationLayer *C_BasePlayer::GetAnimOverlay(int i)
{
	if (i < 15)
		return &GetAnimOverlays()[i];

	return nullptr;
}

int C_BasePlayer::GetNumAnimOverlays()
{
	return *(int*)((DWORD)this + 0x297C);
}

std::array<float, 24> &C_BasePlayer::m_flPoseParameter()
{
	static int _m_flPoseParameter = NetvarSys::Get().GetOffset("CBaseAnimating", "m_flPoseParameter");
	return *(std::array<float, 24>*)((uintptr_t)this + _m_flPoseParameter);
}


bool C_BasePlayer::IsFlying()
{
	if (!this->m_fFlags() & FL_ONGROUND)
	{
		return true;
	}
	return false;
}


int C_BasePlayer::GetSequenceActivity(int sequence)
{
	if (!this->GetModel())
		return -1;

	auto hdr = g_MdlInfo->GetStudioModel(this->GetModel());

	if (!hdr)
		return -1;

	static auto getSequenceActivity = (DWORD)(Utils::FindPatternV2("client_panorama.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74"));
	static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>(getSequenceActivity);

	return GetSequenceActivity(this, hdr, sequence);
}

Vector C_BasePlayer::GetHitboxPos(int hitbox_id)
{
    matrix3x4_t boneMatrix[MAXSTUDIOBONES];

    if(SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
        auto studio_model = g_MdlInfo->GetStudioModel(GetModel());
        if(studio_model) {
            auto hitbox = studio_model->pHitboxSet(0)->pHitbox(hitbox_id);
            if(hitbox) {
                auto
                    min = Vector{},
                    max = Vector{};

                Math::VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min);
                Math::VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max);

                return (min + max) / 2.0f;
            }
        }
    }
    return Vector{};
}

bool C_BasePlayer::GetHitboxPos(int hitbox, Vector &output)
{
    if(hitbox >= HITBOX_MAX)
        return false;

    const model_t *model = this->GetModel();
    if(!model)
        return false;

    studiohdr_t *studioHdr = g_MdlInfo->GetStudioModel(model);
    if(!studioHdr)
        return false;

    matrix3x4_t matrix[MAXSTUDIOBONES];
    if(!this->SetupBones(matrix, MAXSTUDIOBONES, 0x100, 0))
        return false;

    mstudiobbox_t *studioBox = studioHdr->pHitboxSet(0)->pHitbox(hitbox);
    if(!studioBox)
        return false;

    Vector min, max;

    Math::VectorTransform(studioBox->bbmin, matrix[studioBox->bone], min);
    Math::VectorTransform(studioBox->bbmax, matrix[studioBox->bone], max);

    output = (min + max) * 0.5f;

    return true;
}

Vector C_BasePlayer::GetBonePos(int bone)
{
    matrix3x4_t boneMatrix[MAXSTUDIOBONES];

    if(SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0.0f)) {
        return boneMatrix[bone].at(3);
    }
    return Vector{};
}



QAngle* C_BasePlayer::GetVAngles()
{
	static auto deadflag = NetvarSys::Get().GetOffset("DT_BasePlayer", "deadflag");
	return (QAngle*)((uintptr_t)this + deadflag + 0x4);
}



bool C_BasePlayer::CanSeePlayer(C_BasePlayer* player, const Vector& pos)
{
    CGameTrace tr;
    Ray_t ray;
    CTraceFilter filter;
    filter.pSkip = this;

    auto start = GetEyePos();
    auto dir = (pos - start).Normalized();

    ray.Init(start, pos);
    g_EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

    return tr.hit_entity == player || tr.fraction > 0.97f;
}
