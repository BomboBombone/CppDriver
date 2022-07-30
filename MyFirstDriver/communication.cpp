#include "communication.h"

#include <Shared/macros.h>
#include <Shared/message.h>

NTSTATUS Function_IRP_MJ_CREATE(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(Irp);
    UNREFERENCED_PARAMETER(pDeviceObject);

    DbgMsg("IRP MJ CREATE received.");
    return STATUS_SUCCESS;
}

NTSTATUS Function_IRP_MJ_CLOSE(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(Irp);
    UNREFERENCED_PARAMETER(pDeviceObject);

    DbgMsg("IRP MJ CLOSE received.");
    return STATUS_SUCCESS;
}

NTSTATUS Function_IRP_DEVICE_CONTROL(PDEVICE_OBJECT pDeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(pDeviceObject);

    PIO_STACK_LOCATION pIoStackLocation;
    Message<void*> Res((void*)globals::ModuleAddress);
    Message<MESSAGE_TYPE>* pMes = (Message<MESSAGE_TYPE>*) Irp->AssociatedIrp.SystemBuffer;

    pIoStackLocation = IoGetCurrentIrpStackLocation(Irp);
    switch (pIoStackLocation->Parameters.DeviceIoControl.IoControlCode)
    {
    case IO_GET_MODULE_ADDRESS:
        DbgMsg("Message received : %d", pMes->msg);

        RtlZeroMemory(pMes, pIoStackLocation->Parameters.DeviceIoControl.InputBufferLength);
        RtlCopyMemory(pMes, &Res, sizeof(Res));

        break;
    }

    // Finish the I/O operation by simply completing the packet and returning
    // the same status as in the packet itself.
    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = sizeof(Res);
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}