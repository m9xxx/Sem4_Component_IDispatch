#include "interfaces.h"
#include <stdio.h>
#include "Components.h"

//*************************************************

class CA: public IX,IY,IDispatch
{
   private:
    int counter;
    int px1;
   public:
    CA();
    virtual ~CA();

    virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

	virtual void __stdcall Fx1();
	virtual void __stdcall Fy1();

   //IDispatch (Begin)
   virtual HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);
	virtual HRESULT __stdcall Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                                    EXCEPINFO* pExcepInfo, UINT* puArgErr);

   virtual HRESULT __stdcall GetTypeInfoCount(UINT* pctinfo);
	virtual HRESULT __stdcall GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);
   //IDispatch (End)                                  
};

CA::CA()
{
  println("CA::CA");
  counter = 0;
  px1=123;
}

CA::~CA()
{
  println("CA::~CA");
}

HRESULT __stdcall CA::QueryInterface(const IID& iid, void** ppv)
{
   println("CA::QueryInterface");

   if (iid==IID_IUnknown)
   {
      *ppv = (IUnknown*)(IX*)this;
   }
   else if (iid==IID_IX)
   {
      *ppv = (IX*)this;
   }
   else if (iid==IID_IY)
   {
      *ppv = (IY*)this;
   }
   else if (iid==IID_IDispatch)
   {
      *ppv = (IDispatch*)this;
   }
   else
   {
     *ppv = NULL;
     return E_NOINTERFACE;
   }

   this->AddRef();
   return S_OK;
}

ULONG __stdcall CA::AddRef()
{
   println("CA::AddRef");
   counter = counter + 1;
   return counter;
}

ULONG __stdcall CA::Release()
{
   println("CA::Release");
   counter = counter - 1;
   if (counter==0) {delete this;}
   return counter;
}

void __stdcall CA::Fx1()
{
   println("CA:Fx1");
}

void __stdcall CA::Fy1()
{
   println("CA:Fy1");
}


//IDispatch (Begin)
HRESULT __stdcall CA::GetTypeInfoCount(UINT* pctinfo)
{
    println("CA:GetTypeInfoCount");
    return S_OK;
}

HRESULT __stdcall CA::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
{
    println("CA:GetTypeInfo");
    return S_OK;
}

HRESULT __stdcall CA::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
                                    LCID lcid, DISPID* rgDispId)
{
    println("CA:GetIDsOfNames");
    if (cNames!=1) {return E_NOTIMPL;}

    //const wchar_t* src = rgszNames[0];
    //char* dest = new char[32];
    //wcstombs(dest,src,32);
    //printf(dest); printf("\n");

    if (wcscmp(rgszNames[0],L"Fx1")==0)
    {
      rgDispId[0] = 1;
    }
    else if (wcscmp(rgszNames[0],L"Fy1")==0)
    {
      rgDispId[0] = 2;
    }


    //Property
    else if (wcscmp(rgszNames[0],L"Px1")==0)
    {
      rgDispId[0] = 3;
    }
    else
    {
       return E_NOTIMPL;
    }
    return S_OK;
}

HRESULT __stdcall CA::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                             EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
    println("CA:Invoke");
    if (dispIdMember==1)
    {
       Fx1();
    }
    else if (dispIdMember==2)
    {
       Fy1();
    }

    //Property
    else if (dispIdMember==3)
    {
       //printf("%d\n",wFlags);
       if ( (wFlags==DISPATCH_PROPERTYGET) || (wFlags==1) || (wFlags==3) )
       {
          if (pVarResult!=NULL)
          {
            pVarResult->vt = VT_INT;
            pVarResult->intVal = px1;
          }
       }
       else if (wFlags==DISPATCH_PROPERTYPUT)
       {
          DISPPARAMS param = *pDispParams;
          VARIANT arg = (param.rgvarg)[0];
          //printf("%d\n",arg.vt);
          VariantChangeType(&arg,&arg,0,VT_INT);
          //printf("%d\n",arg.vt);
          px1 = arg.intVal;
       }
       else
       {
         return E_NOTIMPL;
       }
    }
    else
    {
      return E_NOTIMPL;
    }
    return S_OK;
}
//IDispatch (End)

//*************************************************

class CFA: public IClassFactory
{
   private:
     int counter;
   public:
      CFA();
      virtual ~CFA();

      virtual HRESULT __stdcall QueryInterface(const IID& iid, void** ppv);
	   virtual ULONG __stdcall AddRef();
	   virtual ULONG __stdcall Release();

	   virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);	   
      virtual HRESULT __stdcall LockServer(BOOL bLock);
};

CFA::CFA()
{
  println("CFA::CFA");
  counter = 0;
}

CFA::~CFA()
{
  println("CFA::~CFA");
}

HRESULT __stdcall CFA::QueryInterface(const IID& iid, void** ppv)
{
   println("CFA::QueryInterface");

   if (iid==IID_IUnknown)
   {
     *ppv = (IUnknown*)(IClassFactory*)this;
   }
   else if (iid==IID_IClassFactory)
   {
     *ppv = (IClassFactory*)this;
   }
   else
   {
     *ppv = NULL;
     return E_NOINTERFACE;
   }
   this->AddRef();
   return S_OK;
}

ULONG __stdcall CFA::AddRef()
{
   println("CFA::AddRef");
   counter = counter + 1;
   return counter;
}

ULONG __stdcall CFA::Release()
{
   println("CFA::Release");
   counter = counter - 1;
   if (counter==0) {delete this;}
   return counter;
}

HRESULT __stdcall CFA::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv)
{
   println("CFA::CreateInstance");
   if (pUnknownOuter!=NULL)
   {
      return E_NOTIMPL;
   };

   CA* a = new CA();
   return a->QueryInterface(iid,ppv);
}

HRESULT __stdcall CFA::LockServer(BOOL bLock)
{
  println("CFA::LockServer");
  return S_OK;
}

//*************************************************


void println(const char* str)
{
    printf(str);
    printf("\n");
}

//{02B2B7C9-166B-413D-90F3-17D5F684592F}
//{91A42CAA-2577-4E80-934E-07DE64502FD6}
const CLSID CLSID_CA = {0x02B2B7C9,0x166B,0x413D,{0x90,0xF3,0x17,0xD5,0xF6,0x84,0x59,0x2F}};

HRESULT __stdcall GetClassObject(const CLSID& clsid, const IID& iid, void** ppv)
{
   println("Component::GetClassObject");
   if (clsid==CLSID_CA)
   {
      CFA* fa  = new CFA();
      return fa->QueryInterface(iid,ppv);
   }
   else
   {
     *ppv = NULL;
     return E_NOTIMPL;
   }

}

//*************************************************
