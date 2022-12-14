//
// Copyright (C) 2005 Vojtech Janota
// Copyright (C) 2003 Xuan Thang Nguyen
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

import inet.common.INETDefs;
import inet.networklayer.contract.ipv4.Ipv4Address;
import inet.networklayer.rsvpte.IntServ;
import inet.networklayer.rsvpte.RsvpPacket;

namespace inet;

//
// FIXME missing documentation
//
class RsvpPathMsg extends RsvpPacket
{
    RsvpHopObj hop;
    LabelRequestObj label_request;
    SenderDescriptor_t sender_descriptor;
    EroVector ERO;
    int color;

    rsvpKind = PATH_MESSAGE;
}

cplusplus(RsvpPathMsg) {{
  public:
    inline Ipv4Address getSrcAddress() { return getSender_descriptor().Sender_Template_Object.SrcAddress; }
    inline int getLspId() const { return getSender_descriptor().Sender_Template_Object.Lsp_Id; }
    inline Ipv4Address getNHOP() { return getHop().Next_Hop_Address; }
    inline Ipv4Address getLIH() { return getHop().Logical_Interface_Handle; }
    inline double getBW() { return getSender_descriptor().Sender_Tspec_Object.req_bandwidth; }
    inline SenderTemplateObj& getSenderTemplateForUpdate() { return getSender_descriptorForUpdate().Sender_Template_Object; }
    inline const SenderTemplateObj& getSenderTemplate() const { return getSender_descriptor().Sender_Template_Object; }
    inline void setSenderTemplate(const SenderTemplateObj& s) { getSender_descriptorForUpdate().Sender_Template_Object = s; }
    inline SenderTspecObj& getSenderTspecForUpdate() { return getSender_descriptorForUpdate().Sender_Tspec_Object; }
    inline const SenderTspecObj& getSenderTspec() { return getSender_descriptor().Sender_Tspec_Object; }
    inline void setSenderTspec(const SenderTspecObj& s) { getSender_descriptorForUpdate().Sender_Tspec_Object = s; }
}}

//
// FIXME missing documentation
//
class RsvpPathTear extends RsvpPacket
{
    RsvpHopObj hop;
    SenderTemplateObj senderTemplate;
    bool force;
    rsvpKind = PTEAR_MESSAGE;
}

cplusplus(RsvpPathTear) {{
  public:
    inline Ipv4Address getNHOP() { return getHop().Next_Hop_Address; }
    inline Ipv4Address getLIH() { return getHop().Logical_Interface_Handle; }
    inline Ipv4Address getSrcAddress() { return getSenderTemplate().SrcAddress; }
    inline int getLspId() const { return getSenderTemplate().Lsp_Id; }
}}
//
// FIXME missing documentation
//
class RsvpPathError extends RsvpPacket
{
    Ipv4Address errorNode;
    int errorCode;
    SenderDescriptor_t sender_descriptor;

    rsvpKind = PERROR_MESSAGE;
}

cplusplus(RsvpPathError) {{
  public:
    inline Ipv4Address getSrcAddress() { return getSender_descriptor().Sender_Template_Object.SrcAddress; }
    inline int getLspId() { return getSender_descriptor().Sender_Template_Object.Lsp_Id; }
    inline double getBW() { return getSender_descriptor().Sender_Tspec_Object.req_bandwidth; }

    inline SenderTemplateObj& getSenderTemplateForUpdate() { return getSender_descriptorForUpdate().Sender_Template_Object; }
    inline const SenderTemplateObj& getSenderTemplate() const { return getSender_descriptor().Sender_Template_Object; }
    inline void setSenderTemplate(const SenderTemplateObj& s) { getSender_descriptorForUpdate().Sender_Template_Object = s; }
    inline SenderTspecObj& getSenderTspecForUpdate() { return getSender_descriptorForUpdate().Sender_Tspec_Object; }
    inline const SenderTspecObj& getSenderTspec() const { return getSender_descriptor().Sender_Tspec_Object; }
    inline void setSenderTspec(const SenderTspecObj& s) { getSender_descriptorForUpdate().Sender_Tspec_Object = s; }
}}
