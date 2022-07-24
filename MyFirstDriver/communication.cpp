#include "communication.h"

#include <Shared/macros.h>

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    DbgMsg("CreateCall called, connection enstablished!\n");

    return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    DbgMsg("Connection terminated!\n");

    return STATUS_SUCCESS;
}

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    NTSTATUS Status = STATUS_UNSUCCESSFUL;
    ULONG ByteIO = 0;

    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

    ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;
    if (ControlCode == IO_GET_CLIENT_ADDRESS) {
        PULONGLONG OutPut = (PULONGLONG)Irp->AssociatedIrp.SystemBuffer;
        *OutPut = globals::ModuleAddress;

        DbgMsg("ModuleAddress requested\n");

        Status = STATUS_SUCCESS;
        ByteIO = sizeof(*OutPut);
    }

    Irp->IoStatus.Status = Status;
    Irp->IoStatus.Information = ByteIO;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return Status;
}
