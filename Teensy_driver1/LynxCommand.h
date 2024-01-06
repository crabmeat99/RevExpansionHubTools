
#ifndef LynxCommand_H_INCLUDED
#define LynxCommand_H_INCLUDED

enum class LynxCommand : unsigned short {
	LynxSetMotorChannelModeCommand = 0x1008,
	LynxSetMotorChannelEnableCommand = 0x100a,
	LynxResetMotorEncoderCommand = 0x100e,
	LynxSetMotorConstantPowerCommand = 0x100f,
	LynxSetMotorTargetVelocityCommand = 0x1011,
	LynxSetMotorTargetPositionCommand = 0x1013,
	LynxGetMotorEncoderPositionCommand = 0x1016,
	LynxSetMotorPIDControlLoopCoefficientsCommand = 0x1017,
	LynxSetServoEnableCommand = 0x1023,
	LynxGetMotorPIDFControlLoopCoefficientsCommand = 0x1035,
	LynxSetSingleDIOOutputCommand = 0x1001,
	LynxSetAllDIOOutputsCommand = 0x1002,
	LynxSetDIODirectionCommand = 0x1003,
	LynxGetSingleDIOInputCommand = 0x1005,
	LynxGetADCCommand = 0x1007,
	LynxIsMotorAtTargetCommand = 0x1015,
	LynxSetServoConfigurationCommand = 0x101f,
	LynxSetServoPulseWidthCommand = 0x1021,
	LynxGetServoPulseWidthCommand = 0x1022,
	LynxI2cWriteSingleByteCommand = 0x1025,
	LynxI2cWriteMultipleBytesCommand = 0x1026,
	LynxI2cReadSingleByteCommand = 0x1027,
	LynxI2cReadMultipleBytesCommand = 0x1028,
	LynxI2cReadStatusQueryCommand = 0x1029,
	LynxI2cWriteStatusQueryCommand = 0x1030,
	LynxI2cConfigureChannelCommand = 0x1031,
	LynxI2cConfigureQueryCommand = 0x102f,
	COMMAND_NUMBER_ACK = 0x7f01,
	COMMAND_NUMBER_GET_MODULE_STATUS = 0x7f03,
	COMMAND_NUMBER_KEEP_ALIVE = 0x7f04,
	COMMAND_NUMBER_DISCOVERY = 0x7f0f,
	COMMAND_NUMBER_DEBUG_LOG_LEVEL = 0x7f0e,
	COMMAND_NUMBER_FAIL_SAFE = 0x7f05
};

#endif