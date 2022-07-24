
#include "driver.h"
#include "events.h"
#include "communication.h"
#include <Shared/macros.h>


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
    UNREFERENCED_PARAMETER(pRegistryPath);

    pDriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
    
    DbgMsg("Driver loading...\n");

    PsSetLoadImageNotifyRoutine(ImageLoadCallback);

    //RtlInitUnicodeString(globals::dev, L"\\Device\\" DRIVER_NAME);
    //RtlInitUnicodeString(globals::dos, L"\\DosDevices\\" DRIVER_NAME);
    //
    //IoCreateDevice(pDriverObject, 0, globals::dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &globals::pDeviceObject);
    //IoCreateSymbolicLink(globals::dos, globals::dev);
    //
    //pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
    //pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
    //pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;
    //
    //if (globals::pDeviceObject) {
    //    globals::pDeviceObject->Flags |= DO_DIRECT_IO;
    //    globals::pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
    //    DbgMsg("Device Object initialized\n");
    //}
    //else {
    //    DbgMsg("Device Object could not be initialized\n");
    //}

    return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
    UNREFERENCED_PARAMETER(pDriverObject);

    DbgMsg("Driver unloading...");

    PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

    //IoDeleteSymbolicLink(globals::dos);
    //IoDeleteDevice(pDriverObject->DeviceObject);

    return STATUS_SUCCESS;
}
