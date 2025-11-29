// ============================================================================
// ملف HowToUseRenderer.cpp - تنفيذ كلاس راسم شاشة التعليمات
// ============================================================================
// هذا الملف يحتوي على جميع الدوال التي تنفذ رسم شاشة التعليمات
// تعرض للمستخدم جميع أوامر التحكم في المحاكاة
// ============================================================================

// تضمين ملف تعريف كلاس راسم شاشة التعليمات
#include "../include/HowToUseRenderer.h"

// تضمين ملف راسم القائمة (للاستفادة من دوال الرسم المشتركة)
#include "../include/MenuRenderer.h"

// تضمين مكتبة OpenGL للرسومات ثلاثية الأبعاد
#include <GL/glut.h>

// ============================================================================
// دالة مساعدة - رسم تعليمة واحدة
// ============================================================================
// هذه الدالة ترسم سطر واحد من التعليمات (المفتاح + الوصف)
// col: العمود (X) لبدء الرسم
// y: الصف (Y) الحالي (يتم تحديثه بعد الرسم)
// key: المفتاح أو الأمر
// desc: وصف الأمر
// spacing: المسافة بين الأسطر
// ============================================================================
void HowToUseRenderer::drawInstruction(float col, float& y, const char* key, const char* desc, float spacing) {
    // تعيين لون فاتح للمفتاح (RGB: 0.7, 0.8, 0.9 = أزرق فاتح)
    glColor3f(0.7f, 0.8f, 0.9f);
    
    // رسم المفتاح في العمود المحدد
    // col + 15: إزاحة صغيرة من اليسار
    MenuRenderer::drawText2D(col + 15, y, key, GLUT_BITMAP_HELVETICA_12);
    
    // تعيين لون أغمق قليلاً للوصف (RGB: 0.5, 0.6, 0.7 = أزرق متوسط)
    glColor3f(0.5f, 0.6f, 0.7f);
    
    // رسم الوصف بجانب المفتاح
    // col + 130: إزاحة أكبر من اليسار (للوصف)
    MenuRenderer::drawText2D(col + 130, y, desc, GLUT_BITMAP_HELVETICA_12);
    
    // تحديث الصف للأسطر التالية (الانتقال للأسفل)
    y -= spacing;
}

// ============================================================================
// دالة الرسم الرئيسية - رسم شاشة التعليمات الكاملة
// ============================================================================
// هذه الدالة تستدعى لرسم شاشة التعليمات بالكامل
// ============================================================================
void HowToUseRenderer::draw() {
    // مسح المخازن المؤقتة (الألوان والعمق)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // حفظ إعدادات الإسقاط الحالية
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // تعيين إسقاط متعامد ثنائي الأبعاد (Orthographic 2D)
    // للرسم على الشاشة مباشرة (بدون منظور)
    gluOrtho2D(0, 800, 0, 600);  // 800×600 = حجم النافذة
    
    // حفظ إعدادات النموذج الحالية
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // إيقاف الإضاءة واختبار العمق للرسم ثنائي الأبعاد
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    // ========================================================================
    // رسم الخلفية المتدرجة
    // ========================================================================
    glBegin(GL_QUADS);
    // اللون في الأسفل (RGB: 0.02, 0.02, 0.08 = أزرق داكن جداً)
    glColor3f(0.02f, 0.02f, 0.08f);
    glVertex2f(0, 0);      // الزاوية السفلية اليسرى
    glVertex2f(800, 0);     // الزاوية السفلية اليمنى
    // اللون في الأعلى (RGB: 0.08, 0.08, 0.18 = أزرق داكن)
    glColor3f(0.08f, 0.08f, 0.18f);
    glVertex2f(800, 600);   // الزاوية العلوية اليمنى
    glVertex2f(0, 600);     // الزاوية العلوية اليسرى
    glEnd();
    
    // ========================================================================
    // رسم العنوان
    // ========================================================================
    // تعيين لون العنوان (RGB: 0.5, 0.7, 1.0 = أزرق فاتح)
    glColor3f(0.5f, 0.7f, 1.0f);
    
    // رسم العنوان في المنتصف (Y = 550)
    MenuRenderer::drawTextCentered(550, "HOW TO USE", GLUT_BITMAP_TIMES_ROMAN_24);
    
    // ========================================================================
    // رسم صندوق المحتوى
    // ========================================================================
    // تعيين لون الصندوق (RGB: 0.1, 0.1, 0.15 = رمادي داكن جداً)
    glColor3f(0.1f, 0.1f, 0.15f);
    
    // رسم صندوق المحتوى
    glBegin(GL_QUADS);
    glVertex2f(50, 50);     // الزاوية السفلية اليسرى
    glVertex2f(750, 50);    // الزاوية السفلية اليمنى
    glVertex2f(750, 500);   // الزاوية العلوية اليمنى
    glVertex2f(50, 500);    // الزاوية العلوية اليسرى
    glEnd();
    
    // رسم إطار الصندوق
    // تعيين لون الإطار (RGB: 0.3, 0.5, 0.8 = أزرق)
    glColor3f(0.3f, 0.5f, 0.8f);
    
    // تعيين سمك الخط
    glLineWidth(2.0f);
    
    // رسم خطوط الإطار
    glBegin(GL_LINE_LOOP);
    glVertex2f(50, 50);     // الزاوية السفلية اليسرى
    glVertex2f(750, 50);    // الزاوية السفلية اليمنى
    glVertex2f(750, 500);   // الزاوية العلوية اليمنى
    glVertex2f(50, 500);    // الزاوية العلوية اليسرى
    glEnd();
    
    // ========================================================================
    // رسم التعليمات
    // ========================================================================
    
    // تحديد مواضع الأعمدة
    float leftCol = 80;      // العمود الأيسر
    float rightCol = 420;    // العمود الأيمن
    
    // تحديد موضع البداية (Y = 460)
    float y = 460;
    
    // تحديد المسافة بين الأسطر
    float lineSpacing = 22;
    
    // ------------------------------------------------------------------------
    // قسم: تحكم الكاميرا (Camera Controls)
    // ------------------------------------------------------------------------
    // تعيين لون العنوان (RGB: 0.9, 0.9, 1.0 = أبيض مزرق)
    glColor3f(0.9f, 0.9f, 1.0f);
    
    // رسم عنوان القسم
    MenuRenderer::drawText2D(leftCol, y, "CAMERA CONTROLS", GLUT_BITMAP_HELVETICA_18);
    
    // الانتقال للأسفل (بمسافة أكبر قليلاً)
    y -= lineSpacing * 1.3f;
    
    // رسم التعليمات
    drawInstruction(leftCol, y, "Mouse Drag", "- Rotate view", lineSpacing);
    drawInstruction(leftCol, y, "W / S Keys", "- Zoom in/out", lineSpacing);
    drawInstruction(leftCol, y, "Mouse Wheel", "- Zoom in/out", lineSpacing);
    
    // مسافة إضافية قبل القسم التالي
    y -= lineSpacing * 0.8f;
    
    // ------------------------------------------------------------------------
    // قسم: تحكم التركيز (Focus Controls)
    // ------------------------------------------------------------------------
    // تعيين لون العنوان
    glColor3f(0.9f, 0.9f, 1.0f);
    
    // رسم عنوان القسم
    MenuRenderer::drawText2D(leftCol, y, "FOCUS CONTROLS", GLUT_BITMAP_HELVETICA_18);
    
    // الانتقال للأسفل
    y -= lineSpacing * 1.3f;
    
    // رسم التعليمات
    drawInstruction(leftCol, y, "Key 0", "- Focus on Sun", lineSpacing);
    drawInstruction(leftCol, y, "Keys 1-8", "- Focus planets", lineSpacing);
    drawInstruction(leftCol, y, "Key 9", "- Overview mode", lineSpacing);
    drawInstruction(leftCol, y, "Key A", "- Auto-rotate", lineSpacing);
    
    // ------------------------------------------------------------------------
    // قسم: مفاتيح الكواكب (Planet Keys) - في العمود الأيمن
    // ------------------------------------------------------------------------
    // إعادة تعيين Y للعمود الأيمن
    y = 460;
    
    // تعيين لون العنوان
    glColor3f(0.9f, 0.9f, 1.0f);
    
    // رسم عنوان القسم
    MenuRenderer::drawText2D(rightCol, y, "PLANET KEYS", GLUT_BITMAP_HELVETICA_18);
    
    // الانتقال للأسفل
    y -= lineSpacing * 1.3f;
    
    // رسم مفاتيح الكواكب
    drawInstruction(rightCol, y, "1", "- Mercury", lineSpacing);
    drawInstruction(rightCol, y, "2", "- Venus", lineSpacing);
    drawInstruction(rightCol, y, "3", "- Earth", lineSpacing);
    drawInstruction(rightCol, y, "4", "- Mars", lineSpacing);
    drawInstruction(rightCol, y, "5", "- Jupiter", lineSpacing);
    drawInstruction(rightCol, y, "6", "- Saturn", lineSpacing);
    drawInstruction(rightCol, y, "7", "- Uranus", lineSpacing);
    drawInstruction(rightCol, y, "8", "- Neptune", lineSpacing);
    
    // مسافة إضافية قبل القسم التالي
    y -= lineSpacing * 0.8f;
    
    // ------------------------------------------------------------------------
    // قسم: أوامر أخرى (Other Controls) - في العمود الأيمن
    // ------------------------------------------------------------------------
    // تعيين لون العنوان
    glColor3f(0.9f, 0.9f, 1.0f);
    
    // رسم عنوان القسم
    MenuRenderer::drawText2D(rightCol, y, "OTHER CONTROLS", GLUT_BITMAP_HELVETICA_18);
    
    // الانتقال للأسفل
    y -= lineSpacing * 1.3f;
    
    // رسم التعليمات
    drawInstruction(rightCol, y, "+ / -", "- Speed control", lineSpacing);
    drawInstruction(rightCol, y, "F11", "- Fullscreen", lineSpacing);
    drawInstruction(rightCol, y, "ESC", "- Return to menu", lineSpacing);
    
    // ========================================================================
    // رسم رسالة العودة للقائمة
    // ========================================================================
    // تعيين لون الرسالة (RGB: 0.6, 0.7, 0.9 = أزرق متوسط)
    glColor3f(0.6f, 0.7f, 0.9f);
    
    // رسم الرسالة في الأسفل (Y = 20)
    MenuRenderer::drawTextCentered(20, "Press ESC or ENTER to return to menu", GLUT_BITMAP_HELVETICA_12);
    
    // ========================================================================
    // تنظيف الإعدادات
    // ========================================================================
    // إعادة تفعيل اختبار العمق
    glEnable(GL_DEPTH_TEST);
    
    // استعادة إعدادات النموذج السابقة
    glPopMatrix();
    
    // استعادة إعدادات الإسقاط السابقة
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    // العودة إلى مصفوفة النموذج
    glMatrixMode(GL_MODELVIEW);
    
    // تبديل المخازن المؤقتة (عرض الإطار المرسوم)
    glutSwapBuffers();
}
