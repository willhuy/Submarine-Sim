def count_obj_elements(file_path):
    counts = {"v": 0, "vn": 0, "f": 0}

    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith("v "):
                counts["v"] += 1
            elif line.startswith("vn "):
                counts["vn"] += 1
            elif line.startswith("f "):
                counts["f"] += 1

    return counts

# Example usage
if __name__ == "__main__":
    #file_path = input("Enter the path to the OBJ file: ").strip()
    counts = count_obj_elements("D:/DAL/3rdYear/csci3161/FinalProject/Submarine-Sim/object_files/coral/coral_14.obj")
    print(f"Counts in file:")
    print(f"Vertices (v): {counts['v']}")
    print(f"Vertex Normals (vn): {counts['vn']}")
    print(f"Faces (f): {counts['f']}")
