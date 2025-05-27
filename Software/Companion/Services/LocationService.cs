using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Companion.Services;

internal sealed class LocationService
{
    public async Task<Location?> GetCurrentLocationAsync()
    {
        try
        {
            var request = new GeolocationRequest
            {
                DesiredAccuracy = GeolocationAccuracy.Medium,
                Timeout = TimeSpan.FromSeconds(10)
            };

            var location = await Geolocation.Default.GetLocationAsync(request);
            return location;
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine($"Unable to get location: {ex.Message}");
            return null;
        }
    }

    public async Task<bool> RequestLocationPermissionAsync()
    {
        try
        {
            var status = await Permissions.RequestAsync<Permissions.LocationWhenInUse>();
            return status == PermissionStatus.Granted;
        }
        catch (Exception ex)
        {
            System.Diagnostics.Debug.WriteLine($"Unable to request location permission: {ex.Message}");
            return false;
        }
    }
}