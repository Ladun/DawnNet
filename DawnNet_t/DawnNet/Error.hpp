#pragma once

#include <DawnNet/Core.hpp>

#define LD_ERRCODE(pErr) const DawnNet::ErrCode pErr = std::hash<std::string>{}(#pErr)   

LD_ERRCODE(eErrCodeSesBufferFull);
LD_ERRCODE(eErrCodeInvalidSize);
LD_ERRCODE(eErrCodeSessionBufferFull);
LD_ERRCODE(eErrCodeInvalidMessage);
LD_ERRCODE(eErrCodeAlreadyRegistered);
LD_ERRCODE(eErrCodeNoInitialize);
LD_ERRCODE(eErrCodeHostNotFound);