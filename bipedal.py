import tkinter as tk
from PIL import ImageTk, Image
import serial
import threading

class App:
    def __init__(self, root):
        self.root = root
        self.root.title("Arduino Serial Image Viewer")
        self.root.geometry("400x400")

        # 1. Initialize Serial Connection (Change 'COM3' or '/dev/ttyUSB0' to match your port)
        try:
            self.ser = serial.Serial('/dev/tty.usbmodem1101', 9600, timeout=1)
        except Exception as e:
            print(f"Could not open serial port: {e}")
            self.ser = None

        # 2. Setup Images
        self.default_img = ImageTk.PhotoImage(Image.new('RGB', (300, 300), color = 'gray'))
        
        # 3. Setup Tkinter Label to display the image
        self.image_label = tk.Label(root, image=self.default_img)
        self.image_label.pack(pady=20)

        # 4. Start the serial reading loop in a separate thread to prevent GUI freezing
        if self.ser and self.ser.is_open:
            self.running = True
            self.thread = threading.Thread(target=self.read_serial)
            self.thread.daemon = True
            self.thread.start()
            
            # Start polling the GUI queue for image updates
            self.root.after(100, self.update_gui)

    def read_serial(self):
        """Continuously reads data from Arduino."""
        while self.running:
            if self.ser.in_waiting > 0:
                line = self.ser.readline().decode('utf-8').strip()
                self.process_serial_data(line)

    def process_serial_data(self, data):
        """Determine which image to load based on serial data."""
        # Example: If Arduino sends "state_1", open "image1.png"
        if data == "1":
            self.load_new_image("1.png")
        elif data == '2':
            self.load_new_image("2.png")
        elif data == '3':
            self.load_new_image("3.png")
        elif data == '4':
            self.load_new_image("4.png")
        elif data == '5':
            self.load_new_image("5.png")
        elif data == '6':
            self.load_new_image("6.png")
        elif data == '7':
            self.load_new_image("7.png")
        elif data == '8':
            self.load_new_image("8.png")
        elif data == '9':
            self.load_new_image("1.png")
            self.load_new_image("2.png")
            self.load_new_image("3.png")
            self.load_new_image("4.png")
            self.load_new_image("5.png")
            self.load_new_image("6.png")
            self.load_new_image("7.png")
            self.load_new_image("8.png")
            self.load_new_image("9.png")
            

    def load_new_image(self, image_path):
        """Safely loads and stores a reference to the new PNG."""
        try:
            loaded_image = Image.open(image_path)
            # Resize if necessary: loaded_image = loaded_image.resize((300, 300))
            self.current_img = ImageTk.PhotoImage(loaded_image)
        except Exception as e:
            print(f"Error loading image: {e}")

    def update_gui(self):
        """Updates the label with the newly loaded image safely in the main thread."""
        if hasattr(self, 'current_img'):
            self.image_label.config(image=self.current_img)
        self.root.after(100, self.update_gui) # Re-run this check every 100ms

    def on_close(self):
        """Closes serial connection safely on exit."""
        self.running = False
        if self.ser and self.ser.is_open:
            self.ser.close()
        self.root.destroy()

# Run the Application
if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.protocol("WM_DELETE_WINDOW", app.on_close)
    root.mainloop()
