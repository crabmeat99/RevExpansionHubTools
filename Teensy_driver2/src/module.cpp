
#include <string.h>
#include <stdlib.h>
#include "rhsp_module.h"
#include "rhsp_compiler.h"
#include "arrayutils.h"
#include "packet.h"
#include "command.h"
#include "module.h"
#include "revhub.h"

int rhsp_getInterfacePacketID(RhspRevHub* hub,
                              const char* interfaceName,
                              uint16_t functionNumber,
                              uint16_t* packetID,
                              uint8_t* nackReasonCode)
{
    if (!hub || !interfaceName)
    {
        return RHSP_ERROR;
    }

    uint16_t packet_id =  0x1000 + functionNumber;
    *packetID = packet_id;
    return RHSP_RESULT_OK;
}

int rhsp_queryInterface(RhspRevHub* hub,
                        const char* interfaceName,
                        uint8_t* nackReasonCode)
{
    size_t interfaceNameLength = strlen(interfaceName) + 1; // interfaceNameLength should include null terminated symbol

    rhsp_assert(interfaceNameLength <= RHSP_MAX_PAYLOAD_SIZE);

    if (!hub || interfaceNameLength > RHSP_MAX_PAYLOAD_SIZE)
    {
        return RHSP_ERROR;
    }

    int result = rhsp_sendReadCommandInternal(hub, 0x7F07, (const uint8_t*) interfaceName,
                                              (uint16_t) interfaceNameLength, nackReasonCode);
    if (result < 0)
    {
        return result;
    }

    return RHSP_RESULT_OK;
}
