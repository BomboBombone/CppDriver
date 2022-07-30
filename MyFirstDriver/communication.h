#pragma once
#include <ntifs.h>
#include <Shared/message.h>

#include "data.h"

NTSTATUS Function_IRP_MJ_CREATE(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Function_IRP_MJ_CLOSE(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS Function_IRP_DEVICE_CONTROL(PDEVICE_OBJECT DeviceObject, PIRP Irp);
//NTSTATUS DispatchPassThru(PDEVICE_OBJECT DeviceObject, PIRP Irp);