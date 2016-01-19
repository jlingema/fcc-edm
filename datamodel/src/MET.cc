// datamodel specific includes
#include "MET.h"
#include "METConst.h"
#include "METObj.h"
#include "METData.h"
#include "METCollection.h"
#include <iostream>




MET::MET() : m_obj(new METObj()){
 m_obj->acquire();
}

MET::MET(float Pt,float Phi) : m_obj(new METObj()){
 m_obj->acquire();
   m_obj->data.Pt = Pt;  m_obj->data.Phi = Phi;
}


MET::MET(const MET& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

MET& MET::operator=(const MET& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

MET::MET(METObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

MET MET::clone() const {
  return {new METObj(*m_obj)};
}

MET::~MET(){
  if ( m_obj != nullptr) m_obj->release();
}

MET::operator ConstMET() const {return ConstMET(m_obj);}

  const float& MET::Pt() const { return m_obj->data.Pt; }
  const float& MET::Phi() const { return m_obj->data.Phi; }

void MET::Pt(float value){ m_obj->data.Pt = value;}
void MET::Phi(float value){ m_obj->data.Phi = value;}


bool  MET::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID MET::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool MET::operator==(const ConstMET& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const MET& p1, const MET& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

