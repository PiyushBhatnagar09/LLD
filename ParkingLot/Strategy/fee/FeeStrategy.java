package LLD.ParkingLot.Strategy.fee;

package LLD.
//parking ticket will contain the details of the vehicle - entry, exit time, type of vehicle
public interface FeeStrategy {
        double calculateFee(ParkingTicket parkingTicket);
}
