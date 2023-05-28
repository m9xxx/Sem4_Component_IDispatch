#include <objbase.h>

#include <stdio.h>

#include "Interfaces.h"


int main()
{
    printf("Main::Start\n");

    try
    {            
      //Initializing COM library (Begin)
      CoInitialize(NULL);
      //Initializing COM library (End)


      //Getting factory (Begin)
      //1
      //{91A42CAA-2577-4E80-934E-07DE64502FD6}      
      //const CLSID CLSID_CA = {0x91A42CAA,0x2577,0x4E80,{0x93,0x4E,0x07,0xDE,0x64,0x50,0x2F,0xD6}};

      //2
      CLSID CLSID_CA_ProgID;      
      {
       const wchar_t* progID = L"IKS.Application";
       //mbstowcs
       //wcstombs
       HRESULT resCLSID_ProgID = CLSIDFromProgID(progID,&CLSID_CA_ProgID);
       if (!(SUCCEEDED(resCLSID_ProgID)))
       {        
         throw "No CLSID form ProgID";         
       }
       else
       {
        printf("CLSID form ProgID OK!");
        printf("\n");
       }
      }
   

      IClassFactory* pCF = NULL;            
      //1
      //HRESULT resFactory = CoGetClassObject(CLSID_CA,CLSCTX_INPROC_SERVER,NULL,IID_IClassFactory,(void**)&pCF);
      //2
      HRESULT resFactory = CoGetClassObject(CLSID_CA_ProgID,CLSCTX_INPROC_SERVER,NULL,IID_IClassFactory,(void**)&pCF);
      if (!(SUCCEEDED(resFactory)))
      {
         //printf("%X\n",(unsigned int)resFactory);
         throw "No factoty";
      }
      //Getting factory (End)



      //Getting instance (Begin)
      //1+2
      IX* pX = NULL;
      HRESULT resInstance = pCF->CreateInstance(NULL,IID_IX,(void**)&pX);
      //3
      //HRESULT resInstance = CoCreateInstance(CLSID_CA,NULL,CLSCTX_INPROC_SERVER,IID_IX,(void**)&pX);
      if (!(SUCCEEDED(resInstance)))
      {
          //printf("%X\n",(unsigned int)resInstance);
          throw "No instance";
      }
      //Getting instance (End)



      //Working (Begin)
      pX->Fx1();
      
      //Querying (Begin)
      IY* pY = NULL;
      HRESULT resQuery = pX->QueryInterface(IID_IY,(void**)&pY);
      if (!(SUCCEEDED(resQuery)))
      {
          //printf("%X\n",(unsigned int)resQuery);
          throw "No query";
      }
      //Querying (End)
      
      pY->Fy1();
      //Working (End)



      //Refering (Begin)
      IY* pY2 = pY;
      pY2->AddRef();
      pY2->Fy1();
      pY2->Release();
      //Refering (End)


      //Dispatch (Begin)
      IDispatch* pDisp = NULL;
      HRESULT resQueryDisp = pX->QueryInterface(IID_IDispatch,(void**)&pDisp);
      if (!(SUCCEEDED(resQueryDisp)))
      {
          //printf("%X\n",(unsigned int)resQuery);
          throw "No query dispatch";
      }

      DISPID dispid;

      int namesCount = 1;
      OLECHAR** names = new OLECHAR*[namesCount];
      OLECHAR* name = const_cast<OLECHAR*>(L"Fy1");
      names[0] = name;
      HRESULT resID_Name = pDisp->GetIDsOfNames(
                                                    IID_NULL_,
                                                    names,
                                                    namesCount,
                                                    GetUserDefaultLCID(),
                                                    &dispid
                                               );
      if (!(SUCCEEDED(resID_Name)))
      {
          //printf("%X\n",(unsigned int)resID_Name);
          printf("No ID of name\n");
      }
      else
      {
         DISPPARAMS dispparamsNoArgs = {
                                         NULL,
                                         NULL,
                                         0,
                                         0,
                                       };

         HRESULT resInvoke = pDisp->Invoke(
                                            dispid, // DISPID
                                            IID_NULL_,
                                            GetUserDefaultLCID(),
                                            DISPATCH_METHOD,
                                            &dispparamsNoArgs,
                                            NULL,
                                            NULL,
                                            NULL
                                          );
        if (!(SUCCEEDED(resInvoke)))
        {
          //printf("%X\n",(unsigned int)resInvoke);
          printf("Invoke error\n");
        }
      }

      pDisp->Release();
      //Dispatch (End)


      //Deleting (Begin)
      pY->Release();
      pX->Release();
      
      pCF->Release();      
      //Deleting (End)

    }
    catch (const char* str)
    {
        printf("Main::Error: ");
        printf(str);
        printf("\n");
    }
    catch (...)
    {
        printf("Main::Error: Unknown\n");
    }

    //2+3
    //Uninitializing COM library (Begin)
    CoUninitialize();
    //Uninitializing COM library (End)
 
    printf("Main::Finish\n");
    return 0;
}