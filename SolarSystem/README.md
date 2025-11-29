# Solar System 3D Simulation

## هيكل المشروع

```
SolarSystem/
├── include/           # ملفات الهيدر (.h)
│   ├── AudioManager.h
│   ├── GameStateManager.h
│   ├── WindowManager.h
│   ├── Camera.h
│   ├── StarField.h
│   ├── Planet.h
│   ├── SolarSystem.h
│   ├── MenuRenderer.h
│   ├── HowToUseRenderer.h
│   ├── AboutRenderer.h
│   ├── Renderer.h
│   ├── InputHandler.h
│   └── MainApp.h
├── src/              # ملفات التنفيذ (.cpp)
│   ├── AudioManager.cpp
│   ├── GameStateManager.cpp
│   ├── WindowManager.cpp
│   ├── Camera.cpp
│   ├── StarField.cpp
│   ├── Planet.cpp
│   ├── SolarSystem.cpp
│   ├── MenuRenderer.cpp
│   ├── HowToUseRenderer.cpp
│   ├── AboutRenderer.cpp
│   ├── Renderer.cpp
│   ├── InputHandler.cpp
│   └── MainApp.cpp
├── obj/              # ملفات الكائنات (يُنشأ تلقائياً)
├── main.cpp          # نقطة الدخول الرئيسية
├── Makefile          # ملف البناء
└── README.md         # هذا الملف

## المتطلبات

- g++
- OpenGL
- GLUT
- SDL2
- SDL2_mixer

## التثبيت على Ubuntu/Debian

```bash
sudo apt-get install g++ freeglut3-dev libsdl2-dev libsdl2-mixer-dev
```

## البناء والتشغيل

### البناء:
```bash
cd SolarSystem
make
```

### التشغيل:
```bash
./solar_system
```

أو:
```bash
make run
```

### التنظيف:
```bash
make clean
```

## وصف الكلاسات

- **AudioManager**: إدارة الصوت والموسيقى
- **GameStateManager**: إدارة حالات اللعبة (القائمة، المحاكاة، إلخ)
- **WindowManager**: إدارة النافذة والشاشة الكاملة
- **Camera**: التحكم بالكاميرا والمشاهدة
- **StarField**: عرض النجوم في الخلفية
- **Planet**: تمثيل كوكب واحد
- **SolarSystem**: إدارة المنظومة الشمسية بالكامل
- **MenuRenderer**: عرض القائمة الرئيسية
- **HowToUseRenderer**: عرض شاشة التعليمات
- **AboutRenderer**: عرض شاشة حول البرنامج
- **Renderer**: المنسق الرئيسي للرسم
- **InputHandler**: معالجة المدخلات
- **MainApp**: التطبيق الرئيسي المنسق

## التحكم

- **الفأرة**: دوران الكاميرا
- **W/S**: تكبير/تصغير
- **0-9**: التركيز على الكواكب
- **A**: الدوران التلقائي
- **ESC**: القائمة الرئيسية
- **F11**: شاشة كاملة
