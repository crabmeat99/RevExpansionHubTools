
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