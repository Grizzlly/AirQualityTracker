using Shiny.BluetoothLE;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Companion.Services;

internal class BLEService(IBleManager bleManager)
{
    internal const int CONNECT_TIMEOUT = 10000;

    internal IPeripheral? Peripheral { get; private set; }

    public List<IPeripheral> Devices { get; } = [];
    public event Action? DevicesUpdated;
    IDisposable? scanSub;

    public ConnectionState State => Peripheral?.Status ?? ConnectionState.Disconnected;
    public event Action<ConnectionState>? ConnectionStateChanged;

    public void StartScan()
    {
        Devices.Clear();
        DevicesUpdated?.Invoke();

        scanSub?.Dispose();
        scanSub = bleManager.Scan(new ScanConfig())
            .Subscribe(res =>
            {
                var device = res.Peripheral;
                if (!Devices.Any(x => x.Uuid == device.Uuid))
                {
                    Devices.Add(device);
                    DevicesUpdated?.Invoke();
                }
            });
    }

    public async Task<bool> ConnectAsync(string serviceUUID)
    {
        var serviceGUID = Guid.Parse(serviceUUID);

        try
        {
            var tcs = new TaskCompletionSource<IPeripheral>();

            using var scan = bleManager.Scan(new ScanConfig { ServiceUuids = [serviceUUID] })
                .Subscribe(res => tcs.TrySetResult(res.Peripheral));

            Peripheral = await Task.WhenAny(tcs.Task, Task.Delay(CONNECT_TIMEOUT)) == tcs.Task
                ? tcs.Task.Result : null;

            if (Peripheral is null)
            {
                return false;
            }

            await Peripheral.ConnectAsync();

            ConnectionStateChanged?.Invoke(State);
            return true;
        }
        catch (Exception)
        {
            return false;
        }
    }

    public async Task<BleCharacteristicResult> ReadCharacteristicAsync(string serviceUUID, string characteristicUUID)
    {
        if (Peripheral is null)
        {
            throw new InvalidOperationException("Not connected to any peripheral.");
        }

        var a = await Peripheral.GetAllCharacteristicsAsync();
        return await Peripheral.ReadCharacteristicAsync(serviceUUID, characteristicUUID);
    }

    public void Stop()
    {
        scanSub?.Dispose();
        scanSub = null;

        Peripheral?.CancelConnection();
        Peripheral = null;
        ConnectionStateChanged?.Invoke(State);
    }
}
