import random

def generate_mars_station_input():
    print("enter the number of requests to be generated:")
    total_events = int(input())
    filename = f"input_{total_events}.txt"
    
    # --- Configuration ---
    # Rovers: Normal, Polar, Digging
    n_rovers = [random.randint(0, 20), random.randint(0, 16), random.randint(0, 12)] 
    # Speeds
    speeds = [random.randint(0, 30), random.randint(0, 18), random.randint(0, 22)]
    # Checkups: N missions before checkup, Checkup Duration (N, P, D)
    checkups = [random.randint(0, 11), random.randint(0, 9), random.randint(0, 12), random.randint(0, 10)]
    
    
    # Lists to track state
    events = []
    mission_id = 1
    current_day = 1
    # Only Normal (N) missions can be aborted in your logic
    active_normal_missions = [] 

    for _ in range(total_events):
        # 20% chance to increment the day, keeping requests clumped
        if random.random() < 0.2:
            current_day += random.randint(0, 1)
        
        # Decide Event Type: 90% New Request, 10% Cancel
        # We can only cancel if we have active Normal missions
        is_cancel = (random.random() < 0.1) and (len(active_normal_missions) > 0)

        if is_cancel:
            # Generate Cancellation (X)
            # Pick a random ID from active normal missions
            target_id = random.choice(active_normal_missions)
            # Remove it so we don't try to cancel it twice
            active_normal_missions.remove(target_id)
            
            # Format: X Day ID
            events.append(f"X {current_day} {target_id}")
        else:
            # Generate New Request (R)
            m_type = random.choice(['N', 'P', 'D','C'])
            
            # Random distance (1000km to 10000km)
            dist = random.randint(1, 10) * 1000
            
            # Random duration (1 to 20 days)
            dur = random.randint(1, 20)
            
            # Format: R Type Day ID Dist Dur
            events.append(f"R {m_type} {current_day} {mission_id} {dist} {dur}")
            
            if m_type == 'N':
                active_normal_missions.append(mission_id)
            
            mission_id += 1

    # --- Write to File ---
    with open(filename, "w") as f:
        # Line 1: Rover Counts
        f.write(f"{n_rovers[0]} {n_rovers[1]} {n_rovers[2]}\n")
        # Line 2: Rover Speeds
        f.write(f"{speeds[0]} {speeds[1]} {speeds[2]}\n")
        # Line 3: Checkup Config
        f.write(f"{checkups[0]} {checkups[1]} {checkups[2]} {checkups[3]}\n")
        # Line 4: Total Events
        f.write(f"{total_events}\n")
        # Events
        for event in events:
            f.write(f"{event}\n")

    print(f"Successfully generated '{filename}' with {total_events} requests!")

if __name__ == "__main__":
    generate_mars_station_input()