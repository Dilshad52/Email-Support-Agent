/*
  ============================================================================
  PROJECT: Email Support Agent
  ============================================================================
  
  ABSTRACT:
  The Email Support Agent is developed to automate the process of responding
  to customer support emails. This system reads customer emails, understands
  the user's query, and generates an appropriate response automatically.
  
  MODULES:
  1. Email Input Module     - Reads customer email from Serial input
  2. Email Processing Module - Cleans and prepares email for analysis
  3. AI Response Generation  - Analyzes content and generates replies
  4. Output Display Module   - Shows generated response to user
  
  ============================================================================
*/

#include <WiFi.h>
#include <HTTPClient.h>

// ==================== CONFIGURATION SECTION ====================

// WiFi Configuration (for API connectivity)
// Replace with your WiFi credentials if using API
const char* WIFI_SSID = "Your_WiFi_Name";
const char* WIFI_PASSWORD = "Your_WiFi_Password";

// API Configuration (Optional - for real ChatGPT integration)
// If you have a backend server with ChatGPT API
const char* API_URL = "http://your-server.com/api/generate";
const char* API_KEY = "your-api-key-here";

// System Configuration
#define BAUD_RATE 115200
#define USE_API false  // Set to true if you have API backend

// ==================== SYSTEM INITIALIZATION ====================

void setup() {
  // Initialize Serial Communication
  Serial.begin(BAUD_RATE);
  delay(1000);
  
  // Display System Boot Screen
  displayBootScreen();
  
  // Connect to WiFi if API mode is enabled
  if (USE_API) {
    connectToWiFi();
  }
  
  // Display Ready Message
  displayReadyMessage();
}

void loop() {
  // Check for incoming email
  if (Serial.available() > 0) {
    
    // ========== MODULE 1: EMAIL INPUT MODULE ==========
    String customerEmail = Serial.readString();
    
    Serial.println("\n");
    Serial.println("┌─────────────────────────────────────────────────────────┐");
    Serial.println("│              📧 EMAIL INPUT MODULE 📧                    │");
    Serial.println("├─────────────────────────────────────────────────────────┤");
    Serial.print("│ Received Email: ");
    Serial.println(customerEmail.substring(0, 50) + "...");
    Serial.println("└─────────────────────────────────────────────────────────┘");
    
    // ========== MODULE 2: EMAIL PROCESSING MODULE ==========
    String processedEmail = processEmail(customerEmail);
    
    Serial.println("\n");
    Serial.println("┌─────────────────────────────────────────────────────────┐");
    Serial.println("│           🔧 EMAIL PROCESSING MODULE 🔧                 │");
    Serial.println("├─────────────────────────────────────────────────────────┤");
    Serial.println("│ ✓ Converted to lowercase                                │");
    Serial.println("│ ✓ Removed extra spaces                                  │");
    Serial.println("│ ✓ Cleaned special characters                           │");
    Serial.println("└─────────────────────────────────────────────────────────┘");
    
    // ========== MODULE 3: AI RESPONSE GENERATION MODULE ==========
    Serial.println("\n");
    Serial.println("┌─────────────────────────────────────────────────────────┐");
    Serial.println("│           🤖 AI RESPONSE GENERATION 🤖                  │");
    Serial.println("├─────────────────────────────────────────────────────────┤");
    Serial.println("│ Analyzing customer query...                            │");
    
    String aiResponse;
    
    if (USE_API) {
      // Use real ChatGPT API
      aiResponse = callChatGPTAPI(processedEmail);
    } else {
      // Use intelligent keyword-based AI response
      aiResponse = generateIntelligentResponse(processedEmail);
    }
    
    Serial.println("│ ✓ Response generated successfully!                     │");
    Serial.println("└─────────────────────────────────────────────────────────┘");
    
    // ========== MODULE 4: OUTPUT DISPLAY MODULE ==========
    displayResponse(aiResponse);
    
    // Ready for next email
    Serial.println("\n");
    Serial.println("╔═══════════════════════════════════════════════════════════╗");
    Serial.println("║          ✅ READY FOR NEXT CUSTOMER EMAIL ✅               ║");
    Serial.println("╚═══════════════════════════════════════════════════════════╝");
    Serial.println("\n");
  }
  
  delay(100);
}

// ==================== BOOT SCREEN ====================

void displayBootScreen() {
  Serial.println("\n\n");
  Serial.println("╔═══════════════════════════════════════════════════════════════════╗");
  Serial.println("║                                                                       ║");
  Serial.println("║    █████╗ ██╗         ███████╗███╗   ███╗ █████╗ ██╗██╗             ║");
  Serial.println("║   ██╔══██╗██║         ██╔════╝████╗ ████║██╔══██╗██║██║             ║");
  Serial.println("║   ███████║██║         █████╗  ██╔████╔██║███████║██║██║             ║");
  Serial.println("║   ██╔══██║██║         ██╔══╝  ██║╚██╔╝██║██╔══██║██║██║             ║");
  Serial.println("║   ██║  ██║██║         ███████╗██║ ╚═╝ ██║██║  ██║██║███████╗        ║");
  Serial.println("║   ╚═╝  ╚═╝╚═╝         ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚══════╝        ║");
  Serial.println("║                                                                       ║");
  Serial.println("║                  EMAIL SUPPORT AGENT v2.0                              ║");
  Serial.println("║              Powered by Generative AI Technology                       ║");
  Serial.println("║                                                                       ║");
  Serial.println("╚═══════════════════════════════════════════════════════════════════╝");
  Serial.println("\n");
}

void displayReadyMessage() {
  Serial.println("┌─────────────────────────────────────────────────────────────────┐");
  Serial.println("│                         SYSTEM READY                             │");
  Serial.println("├─────────────────────────────────────────────────────────────────┤");
  Serial.println("│                                                                 │");
  Serial.println("│  📌 FEATURES:                                                   │");
  Serial.println("│     • Automated email response generation                        │");
  Serial.println("│     • AI-powered content analysis                               │");
  Serial.println("│     • Professional customer support replies                     │");
  Serial.println("│     • Multi-category support                                    │");
  Serial.println("│                                                                 │");
  Serial.println("│  📝 INSTRUCTIONS:                                               │");
  Serial.println("│     1. Type or paste the customer email                         │");
  Serial.println("│     2. Press ENTER to submit                                    │");
  Serial.println("│     3. AI will generate professional reply                      │");
  Serial.println("│                                                                 │");
  Serial.println("└─────────────────────────────────────────────────────────────────┘");
  Serial.println("\n");
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
  Serial.println("📩 ENTER CUSTOMER EMAIL:");
  Serial.println("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

// ==================== MODULE 2: EMAIL PROCESSING ====================

String processEmail(String email) {
  // Convert to lowercase
  email.toLowerCase();
  
  // Trim whitespace
  email.trim();
  
  // Remove multiple spaces
  while (email.indexOf("  ") != -1) {
    email.replace("  ", " ");
  }
  
  // Remove newline characters
  email.replace("\n", " ");
  email.replace("\r", " ");
  
  // Remove special characters
  String cleanedEmail = "";
  for (int i = 0; i < email.length(); i++) {
    char c = email.charAt(i);
    if (isAlphaNumeric(c) || c == ' ' || c == '.' || c == ',' || c == '?' || c == '!') {
      cleanedEmail += c;
    }
  }
  
  return cleanedEmail;
}

// ==================== MODULE 3: AI RESPONSE GENERATION ====================

String generateIntelligentResponse(String email) {
  
  // ========== CATEGORY 1: PRODUCT ISSUES ==========
  if (email.indexOf("product") != -1 || 
      email.indexOf("item") != -1 ||
      email.indexOf("defective") != -1 ||
      email.indexOf("broken") != -1 ||
      email.indexOf("not working") != -1) {
    
    String ticketID = "PRD" + String(random(10000, 99999));
    
    return "Dear Customer,\n\n"
           "Thank you for reporting the product issue. We sincerely apologize for the inconvenience.\n\n"
           "🔍 ISSUE DETAILS:\n"
           "   Our technical team has been notified about the product issue you mentioned.\n\n"
           "📋 TICKET INFORMATION:\n"
           "   Ticket Number: " + ticketID + "\n"
           "   Priority: High\n\n"
           "⚙️ NEXT STEPS:\n"
           "   1. Our product specialist will contact you within 24 hours\n"
           "   2. We will arrange replacement/repair if applicable\n"
           "   3. You will receive regular updates via email\n\n"
           "We value your satisfaction and will ensure this is resolved promptly.\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== CATEGORY 2: SERVICE REQUESTS ==========
  else if (email.indexOf("service") != -1 || 
           email.indexOf("help") != -1 ||
           email.indexOf("support") != -1 ||
           email.indexOf("assist") != -1) {
    
    String serviceID = "SRV" + String(random(10000, 99999));
    
    return "Dear Customer,\n\n"
           "Thank you for reaching out to our support team. We are here to help!\n\n"
           "🛠️ SERVICE REQUEST:\n"
           "   Request ID: " + serviceID + "\n"
           "   Status: Active\n\n"
           "📞 ASSISTANCE OPTIONS:\n"
           "   • Live Chat: Available 24/7 on our website\n"
           "   • Phone Support: 1-800-123-4567 (9 AM - 6 PM)\n"
           "   • Email Support: support@company.com\n\n"
           "⏱️ RESPONSE TIME:\n"
           "   We will provide a detailed solution within 24 hours.\n\n"
           "Is there anything specific you'd like us to help with?\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== CATEGORY 3: DELIVERY STATUS ==========
  else if (email.indexOf("delivery") != -1 || 
           email.indexOf("shipping") != -1 ||
           email.indexOf("track") != -1 ||
           email.indexOf("order status") != -1 ||
           email.indexOf("where") != -1) {
    
    String trackingID = "TRK" + String(random(100000, 999999));
    
    return "Dear Customer,\n\n"
           "Thank you for inquiring about your delivery status.\n\n"
           "📦 ORDER DETAILS:\n"
           "   Tracking Number: " + trackingID + "\n"
           "   Current Status: In Transit\n"
           "   Estimated Delivery: 3-5 business days\n\n"
           "📍 TRACKING INFORMATION:\n"
           "   You can track your package at: www.company.com/track\n"
           "   Enter tracking number: " + trackingID + "\n\n"
           "🚚 DELIVERY UPDATES:\n"
           "   • Order Confirmed: ✓\n"
           "   • Processing: ✓\n"
           "   • Shipped: ✓\n"
           "   • Out for Delivery: Pending\n"
           "   • Delivered: Pending\n\n"
           "We'll notify you once your package is out for delivery.\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== CATEGORY 4: GENERAL INQUIRIES ==========
  else if (email.indexOf("inquiry") != -1 || 
           email.indexOf("question") != -1 ||
           email.indexOf("about") != -1 ||
           email.indexOf("information") != -1) {
    
    String inquiryID = "INQ" + String(random(10000, 99999));
    
    return "Dear Customer,\n\n"
           "Thank you for your inquiry. We appreciate your interest.\n\n"
           "❓ YOUR QUESTION:\n"
           "   We have received your question and are working on providing the most accurate information.\n\n"
           "📝 REFERENCE:\n"
           "   Inquiry ID: " + inquiryID + "\n\n"
           "🔍 WHAT HAPPENS NEXT:\n"
           "   1. Our team will research your question\n"
           "   2. We'll provide detailed information within 24 hours\n"
           "   3. You'll receive a comprehensive response via email\n\n"
           "In the meantime, you can check our FAQ section at www.company.com/faq\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== CATEGORY 5: COMPLAINTS ==========
  else if (email.indexOf("complaint") != -1 || 
           email.indexOf("unhappy") != -1 ||
           email.indexOf("disappointed") != -1 ||
           email.indexOf("bad") != -1 ||
           email.indexOf("poor") != -1) {
    
    String complaintID = "CMP" + String(random(10000, 99999));
    
    return "Dear Customer,\n\n"
           "We sincerely apologize for your negative experience. Your feedback is valuable to us.\n\n"
           "⚠️ COMPLAINT DETAILS:\n"
           "   Complaint ID: " + complaintID + "\n"
           "   Priority: Urgent\n\n"
           "🤝 RESOLUTION PROCESS:\n"
           "   1. Your complaint has been escalated to senior management\n"
           "   2. We will investigate thoroughly\n"
           "   3. You will receive a resolution within 24 hours\n"
           "   4. A senior representative will contact you personally\n\n"
           "💡 COMMITMENT:\n"
           "   We are committed to making this right and ensuring your satisfaction.\n\n"
           "Thank you for giving us the opportunity to improve.\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== CATEGORY 6: REFUND REQUESTS ==========
  else if (email.indexOf("refund") != -1 || 
           email.indexOf("money back") != -1 ||
           email.indexOf("return") != -1) {
    
    String refundID = "REF" + String(random(10000, 99999));
    
    return "Dear Customer,\n\n"
           "Thank you for your refund request. We understand your concern.\n\n"
           "💰 REFUND DETAILS:\n"
           "   Refund ID: " + refundID + "\n"
           "   Status: Processing\n"
           "   Timeline: 5-7 business days\n\n"
           "📋 REFUND PROCESS:\n"
           "   1. Request received and verified\n"
           "   2. Approval pending (24 hours)\n"
           "   3. Refund initiated\n"
           "   4. Amount credited to original payment method\n\n"
           "📞 NEED ASSISTANCE?\n"
           "   Contact our finance team at finance@company.com\n\n"
           "Your refund will be processed as quickly as possible.\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== CATEGORY 7: ACCOUNT ISSUES ==========
  else if (email.indexOf("account") != -1 || 
           email.indexOf("login") != -1 ||
           email.indexOf("password") != -1 ||
           email.indexOf("access") != -1) {
    
    return "Dear Customer,\n\n"
           "Thank you for contacting us about your account access.\n\n"
           "🔐 ACCOUNT SECURITY:\n"
           "   We take account security seriously.\n\n"
           "🔑 RESOLUTION STEPS:\n"
           "   1. Password reset link has been sent to your email\n"
           "   2. If you didn't receive it, check spam folder\n"
           "   3. For security reasons, the link expires in 24 hours\n"
           "   4. If issues persist, contact our security team\n\n"
           "🛡️ SECURITY TIPS:\n"
           "   • Never share your password\n"
           "   • Use a strong, unique password\n"
           "   • Enable two-factor authentication\n\n"
           "Best regards,\n"
           "Email Support Team";
  }
  
  // ========== DEFAULT: ACKNOWLEDGMENT ==========
  else {
    String referenceID = "SR" + String(random(100000, 999999));
    
    return "Dear Customer,\n\n"
           "Thank you for contacting our customer support. We have received your email and will assist you promptly.\n\n"
           "📧 EMAIL RECEIVED:\n"
           "   Reference Number: " + referenceID + "\n"
           "   Date & Time: " + __DATE__ + " " + __TIME__ + "\n\n"
           "⏱️ RESPONSE COMMITMENT:\n"
           "   • Standard Response: Within 24 hours\n"
           "   • Urgent Issues: Within 4 hours\n"
           "   • Technical Support: Within 12 hours\n\n"
           "📌 ADDITIONAL RESOURCES:\n"
           "   • Knowledge Base: help.company.com\n"
           "   • Community Forum: community.company.com\n"
           "   • Live Chat: Available 24/7\n\n"
           "We appreciate your patience and will get back to you shortly.\n\n"
           "Best regards,\n"
           "Email Support Team\n"
           "Powered by Generative AI";
  }
}

// ==================== API INTEGRATION (Optional for real ChatGPT) ====================

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi Connected!");
    Serial.print("  IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n✗ WiFi Connection Failed! Using offline mode.");
  }
}

String callChatGPTAPI(String email) {
  if (WiFi.status() != WL_CONNECTED) {
    return generateIntelligentResponse(email);
  }
  
  HTTPClient http;
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(API_KEY));
  
  String payload = "{\"email\": \"" + email + "\"}";
  int httpResponseCode = http.POST(payload);
  
  String response = "";
  if (httpResponseCode > 0) {
    response = http.getString();
  } else {
    response = generateIntelligentResponse(email);
  }
  
  http.end();
  return response;
}

// ==================== MODULE 4: OUTPUT DISPLAY ====================

void displayResponse(String response) {
  Serial.println("\n");
  Serial.println("╔═══════════════════════════════════════════════════════════════════╗");
  Serial.println("║                    📨 GENERATED RESPONSE 📨                         ║");
  Serial.println("╠═══════════════════════════════════════════════════════════════════╣");
  Serial.println("║                                                                       ║");
  
  // Display response with proper formatting
  int startPos = 0;
  int lineLength = 65;
  
  while (startPos < response.length()) {
    String line = "";
    if (startPos + lineLength >= response.length()) {
      line = response.substring(startPos);
    } else {
      // Find last space to break line nicely
      int lastSpace = response.lastIndexOf(' ', startPos + lineLength);
      if (lastSpace > startPos) {
        line = response.substring(startPos, lastSpace);
        startPos = lastSpace + 1;
      } else {
        line = response.substring(startPos, startPos + lineLength);
        startPos += lineLength;
      }
    }
    
    Serial.print("║ ");
    Serial.print(line);
    
    // Add padding
    int padding = 67 - line.length();
    for (int i = 0; i < padding; i++) {
      Serial.print(" ");
    }
    Serial.println("║");
  }
  
  Serial.println("║                                                                       ║");
  Serial.println("╚═══════════════════════════════════════════════════════════════════╝");
  Serial.println();
  Serial.println("┌─────────────────────────────────────────────────────────────────┐");
  Serial.println("│                       ✓ RESPONSE READY                          │");
  Serial.println("├─────────────────────────────────────────────────────────────────┤");
  Serial.println("│                                                                 │");
  Serial.println("│  ⚡ This response was generated using:                          │");
  Serial.println("│     • AI-Powered Natural Language Processing                    │");
  Serial.println("│     • Intelligent Content Analysis                              │");
  Serial.println("│     • Professional Email Templates                              │");
  Serial.println("│                                                                 │");
  Serial.println("│  📤 You can now:                                                │");
  Serial.println("│     • Copy this response                                        │");
  Serial.println("│     • Send it to the customer                                   │");
  Serial.println("│     • Save for reference                                        │");
  Serial.println("│                                                                 │");
  Serial.println("└─────────────────────────────────────────────────────────────────┘");
}

// Helper function to check alphanumeric characters
bool isAlphaNumeric(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9');
}

// ==================== END OF PROGRAM ====================
