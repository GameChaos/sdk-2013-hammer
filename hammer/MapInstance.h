﻿#ifndef MAPINSTANCE_H
#define MAPINSTANCE_H

#pragma once

#include "MapHelper.h"
#include "utlstring.h"

class CHelperInfo;

class CMapInstance : public CMapHelper
{
public:
	DECLARE_MAPCLASS( CMapInstance, CMapHelper )

	static CMapClass* Create( CHelperInfo* pHelperInfo, CMapEntity* pParent );
	CMapInstance();
	CMapInstance( CMapEntity* pParent );
	~CMapInstance() override;

	size_t GetSize() override { return sizeof(*this); }

	CMapClass* Copy( bool bUpdateDependencies ) override;
	CMapClass* CopyFrom( CMapClass* pFrom, bool bUpdateDependencies ) override;

	void UpdateDependencies( CMapWorld* pWorld, CMapClass* pObject ) override;
	void SetParent( CMapAtom* pParent ) override;
	SelectionState_t SetSelectionState( SelectionState_t eSelectionState ) override;

	void SetOrigin( Vector& pfOrigin ) override;
	void SetCullBoxFromFaceList( CMapFaceList* pFaces ) override;
	void CalcBounds( BOOL bFullUpdate ) override;
	void GetCullBox( Vector& mins, Vector& maxs ) override;
	bool GetCullBoxChild(Vector& mins, Vector& maxs) override;
	void GetRender2DBox( Vector& mins, Vector& maxs ) override;
	bool GetRender2DBoxChild( Vector& mins, Vector& maxs ) override;
	void GetBoundsCenter( Vector& vecCenter ) override;
	bool GetBoundsCenterChild( Vector& vecCenter ) override;
	void GetBoundsSize( Vector& vecSize ) override;
	bool GetBoundsSizeChild( Vector& vecSize ) override;
	void DoTransform( const VMatrix& matrix ) override;
	bool PostloadVisGroups(bool bIsLoading) override;

	bool HitTest2D( CMapView2D* pView, const Vector2D& point, HitInfo_t& HitData ) override;
	bool IsCulledByCordon( const Vector& vecMins, const Vector& vecMaxs ) override;
	bool IsInsideBox( Vector const& Mins, Vector const& Maxs ) const override;
	bool IsIntersectingBox( const Vector& vecMins, const Vector& vecMaxs ) const override;

	bool IsVisualElement() override { return true; }
	void OnParentKeyChanged( const char* key, const char* value ) override;
	void Render2D( CRender2D* pRender ) override;
	void Render3D( CRender3D* pRender ) override;
	bool RenderPreload( CRender3D* pRender, bool bNewContext ) override;
	void AddShadowingTriangles( CUtlVector<Vector>& tri_list ) override;

	[[nodiscard]] bool Collapse( bool bRecursive, InstanceCollapseData_t& collapseData );
private:
	void LoadVMF( CMapClass* pParent = nullptr );
	bool LoadVMFInternal( const char* pVMFPath );
	void Render2DChildren( CRender2D* pRender, CMapClass* pEnt );
	void Render3DChildren( CRender3D* pRender, CUtlVector<CMapClass*>& deferred, CMapClass* pEnt, bool ignoreFrameCount );
	void Render3DChildrenDeferred( CRender3D* pRender, CMapClass* pEnt, bool ignoreFrameCount );
	void AddShadowingTrianglesChildren( CUtlVector<Vector>& tri_list, CMapClass* pEnt );
	template <BoundBox CMapClass::* type>
	void GetBounds( Vector& mins, Vector& maxs ) const;
	static void FixAngles( QAngle& angle );
	void DecompressMatrix( Vector& origin, QAngle& angle ) const;
	void ConstructMatrix( const Vector& origin, const QAngle& angle );
	template <size_t N>
	static bool DeterminePath( const char* pszBaseFileName, const char* pszInstanceFileName, char( &pszOutFileName )[N] );

	CMapWorld* m_pTemplate;
	CUtlString m_strCurrentVMF;
	CUtlString m_strPreviousVMF;
	VMatrix m_matTransform;
};

#endif // MAPINSTANCE_H
